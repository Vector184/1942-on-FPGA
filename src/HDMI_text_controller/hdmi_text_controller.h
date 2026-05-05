#ifndef HDMI_TEXT_CONTROLLER_H
#define HDMI_TEXT_CONTROLLER_H


/****************** Include Files ********************/
#include <stdint.h>
#include "xil_types.h"
#include "xil_io.h"
#include "xstatus.h"
#include "xparameters.h"

#define HDMI_OAM_REGISTER_COUNT 32

typedef struct {
	uint8_t y;
	uint8_t tile_index;
	uint8_t attributes;
	uint8_t x;
} HdmiOamSpriteEntry;

struct OAM {
	uint32_t OAM_reg[HDMI_OAM_REGISTER_COUNT];
	uint32_t OAM_BKG;
};


//you may have to change this line depending on your platform designer
#define OAM_ctrl ((volatile struct OAM*)(uintptr_t)XPAR_HDMI_TEXT_CONTROLLER_0_AXI_BASEADDR)

/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a HDMI_TEXT_CONTROLLER register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the HDMI_TEXT_CONTROLLERdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void HDMI_TEXT_CONTROLLER_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define HDMI_TEXT_CONTROLLER_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a HDMI_TEXT_CONTROLLER register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the HDMI_TEXT_CONTROLLER device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 HDMI_TEXT_CONTROLLER_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define HDMI_TEXT_CONTROLLER_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the HDMI_TEXT_CONTROLLER instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
 

#ifdef __cplusplus
extern "C" {
#endif

uint32_t packOamSpriteEntry(HdmiOamSpriteEntry entry);
void commitFrameRaw(const HdmiOamSpriteEntry* entries, uint32_t count);
void setBackgroundSpriteRegister(uint32_t backgroundSpriteId);
void textHDMIColorClr();
void textHDMIDrawColorText(char* str, int x, int y, uint8_t background, uint8_t foreground);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "../../includes/Sprite.hpp"

inline void commitFrame(const InternalSprite* const* entries, uint32_t count, uint32_t backgroundSpriteId)
{
	uint32_t cappedCount = count < HDMI_OAM_REGISTER_COUNT ? count : HDMI_OAM_REGISTER_COUNT;

	for (uint32_t i = 0; i < HDMI_OAM_REGISTER_COUNT; ++i) {
		uint32_t packed = 0;

		if (entries != nullptr && i < cappedCount && entries[i] != nullptr) {
			packed = entries[i]->packOamEntry();
		}

		OAM_ctrl->OAM_reg[i] = packed;
	}

	setBackgroundSpriteRegister(backgroundSpriteId);
}
#endif

#endif // HDMI_TEXT_CONTROLLER_H
