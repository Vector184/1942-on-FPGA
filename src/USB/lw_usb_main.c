#include <stdio.h>
#include "platform.h"
#include "lw_usb/GenericMacros.h"
#include "lw_usb/GenericTypeDefs.h"
#include "lw_usb/MAX3421E.h"
#include "lw_usb/USB.h"
#include "lw_usb/usb_ch9.h"
#include "lw_usb/transfer.h"
#include "lw_usb/HID.h"
#include "usb_keyboard.h"
#include "xparameters.h"

#ifdef XPAR_GPIO_USB_KEYCODE_DEVICE_ID
#include <xgpio.h>
#endif

extern HID_DEVICE hid_device;

static BYTE addr = 1; 				//hard-wired USB address
const char* const devclasses[] = { " Uninitialized", " HID Keyboard", " HID Mouse", " Mass storage" };
BOOT_KBD_REPORT kbdbuf;

#ifdef XPAR_GPIO_USB_KEYCODE_DEVICE_ID
static XGpio Gpio_hex;
#endif

static BOOT_MOUSE_REPORT mousebuf;
static BYTE runningdebugflag = 0;
static BYTE errorflag = 0;
static BYTE device = 0xFF;
static BOOL usb_initialized = FALSE;

BYTE GetDriverandReport() {
	BYTE i;
	BYTE rcode;
	BYTE device = 0xFF;
	BYTE tmpbyte;

	DEV_RECORD* tpl_ptr;
	xil_printf("Reached USB_STATE_RUNNING (0x40)\n");
	for (i = 1; i < USB_NUMDEVICES; i++) {
		tpl_ptr = GetDevtable(i);
		if (tpl_ptr->epinfo != NULL) {
			xil_printf("Device: %d", i);
			xil_printf("%s \n", devclasses[tpl_ptr->devclass]);
			device = tpl_ptr->devclass;
		}
	}
	//Query rate and protocol
	rcode = XferGetIdle(addr, 0, hid_device.interface, 0, &tmpbyte);
	if (rcode) {   //error handling
		xil_printf("GetIdle Error. Error code: ");
		xil_printf("%x \n", rcode);
	} else {
		xil_printf("Update rate: ");
		xil_printf("%x \n", tmpbyte);
	}
	xil_printf("Protocol: ");
	rcode = XferGetProto(addr, 0, hid_device.interface, &tmpbyte);
	if (rcode) {   //error handling
		xil_printf("GetProto Error. Error code ");
		xil_printf("%x \n", rcode);
	} else {
		xil_printf("%d \n", tmpbyte);
	}
	return device;
}

#ifdef XPAR_GPIO_USB_KEYCODE_DEVICE_ID
static void printHex(u32 data, unsigned channel)
{
	XGpio_DiscreteWrite(&Gpio_hex, channel, data);
}
#endif

void USBKeyboard_Init(void) {
	if (usb_initialized) {
		return;
	}

	init_platform();

#ifdef XPAR_GPIO_USB_KEYCODE_DEVICE_ID
	XGpio_Initialize(&Gpio_hex, XPAR_GPIO_USB_KEYCODE_DEVICE_ID);
	XGpio_SetDataDirection(&Gpio_hex, 1, 0x00000000);
	XGpio_SetDataDirection(&Gpio_hex, 2, 0x00000000);
#endif

	xil_printf("initializing MAX3421E...\n");
	MAX3421E_init();
	xil_printf("initializing USB...\n");
	USB_init();

	usb_initialized = TRUE;
}

void USBKeyboard_Task(void) {
	BYTE rcode;

	if (!usb_initialized) {
		USBKeyboard_Init();
	}

	MAX3421E_Task();
	USB_Task();
	if (GetUsbTaskState() == USB_STATE_RUNNING) {
		if (!runningdebugflag) {
			runningdebugflag = 1;
			device = GetDriverandReport();
		} else if (device == HID_K) {
			rcode = kbdPoll(&kbdbuf);
			if (rcode == hrNAK) {
				return;
			} else if (rcode) {
				xil_printf("Keyboard rcode: ");
				xil_printf("%x \n", rcode);
				return;
			}
#ifdef XPAR_GPIO_USB_KEYCODE_DEVICE_ID
			printHex((u32)kbdbuf.keycode[0] + ((u32)kbdbuf.keycode[1] << 8) + ((u32)kbdbuf.keycode[2] << 16) + ((u32)kbdbuf.keycode[3] << 24), 1);
			printHex((u32)kbdbuf.keycode[4] + ((u32)kbdbuf.keycode[5] << 8), 2);
#endif
		} else if (device == HID_M) {
			rcode = mousePoll(&mousebuf);
			if (rcode == hrNAK) {
				return;
			} else if (rcode) {
				xil_printf("Mouse rcode: ");
				xil_printf("%x \n", rcode);
				return;
			}
		}
	} else if (GetUsbTaskState() == USB_STATE_ERROR) {
		if (!errorflag) {
			errorflag = 1;
			xil_printf("USB Error State\n");
		}
	} else {
		if (runningdebugflag) {
			runningdebugflag = 0;
			MAX3421E_init();
			USB_init();
		}
		errorflag = 0;
		device = 0xFF;
	}
}

void USBKeyboard_Cleanup(void) {
	if (usb_initialized) {
		cleanup_platform();
		usb_initialized = FALSE;
	}
}

const BOOT_KBD_REPORT* USBKeyboard_GetReport(void) {
	return &kbdbuf;
}

BOOL USBKeyboard_IsKeyPressed(BYTE keycode) {
	int i;

	for (i = 0; i < 6; i++) {
		if (kbdbuf.keycode[i] == keycode) {
			return TRUE;
		}
	}
	return FALSE;
}

/*#ifdef USB_STANDALONE_MAIN
int main() {
    USBKeyboard_Init();
	while (1) {
		xil_printf("."); //A tick here means one loop through the USB main handler
		USBKeyboard_Task();
	}
    USBKeyboard_Cleanup();
	return 0;
}
#endif*/
