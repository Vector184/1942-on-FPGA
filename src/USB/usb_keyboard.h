#ifndef USB_KEYBOARD_H
#define USB_KEYBOARD_H

#include "lw_usb/GenericTypeDefs.h"
#include "lw_usb/HID.h"

#ifdef __cplusplus
extern "C" {
#endif

extern BOOT_KBD_REPORT kbdbuf;

void USBKeyboard_Init(void);
void USBKeyboard_Task(void);
void USBKeyboard_Cleanup(void);
const BOOT_KBD_REPORT* USBKeyboard_GetReport(void);
BOOL USBKeyboard_IsKeyPressed(BYTE keycode);

#ifdef __cplusplus
}
#endif

#endif
