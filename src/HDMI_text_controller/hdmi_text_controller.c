

/***************************** Include Files *******************************/
#include "hdmi_text_controller.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sleep.h"

/************************** Function Definitions ***************************/

uint32_t packOamSpriteEntry(HdmiOamSpriteEntry entry)
{
	return ((uint32_t)entry.y) |
	       ((uint32_t)entry.tile_index << 8) |
	       ((uint32_t)entry.attributes << 16) |
	       ((uint32_t)entry.x << 24);
}
void commitFrameRaw(const HdmiOamSpriteEntry* entries, uint32_t count)
{
	uint32_t cappedCount = count < HDMI_OAM_REGISTER_COUNT ? count : HDMI_OAM_REGISTER_COUNT;

	for (uint32_t i = 0; i < HDMI_OAM_REGISTER_COUNT; ++i)
	{
		uint32_t packed = 0;

		if (entries != NULL && i < cappedCount)
		{
			packed = packOamSpriteEntry(entries[i]);
		}

		OAM_ctrl->OAM_reg[i] = packed;
	}
}

void setBackgroundSpriteRegister(uint32_t backgroundSpriteId)
{
	OAM_ctrl->OAM_BKG = backgroundSpriteId;
}

void textHDMIColorClr()
{
	for (int i = 0; i < HDMI_OAM_REGISTER_COUNT; i++)
	{
		OAM_ctrl->OAM_reg[i] = 0x00;
	}
	setBackgroundSpriteRegister(0);
}

void textHDMIDrawColorText(char* str, int x, int y, uint8_t background, uint8_t foreground)
{
	int i = 0;
	int start = y + x;

	while (str[i] != 0 && (start + i) < HDMI_OAM_REGISTER_COUNT)
	{
		OAM_ctrl->OAM_reg[start + i] =
			((uint32_t)(foreground << 4 | background) << 8) |
			(uint8_t)str[i];
		i++;
	}
}
