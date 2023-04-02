#include "Utils.h"

int Utils::GetDX(lv_align_t align)
{
	switch (align)
	{
	case LV_ALIGN_DEFAULT:
		return 0;
	case LV_ALIGN_BOTTOM_LEFT:
		return 5;
	case LV_ALIGN_BOTTOM_MID:
		return 0;
	case LV_ALIGN_BOTTOM_RIGHT:
		return 5;
	case LV_ALIGN_CENTER:
		return 0;
	case LV_ALIGN_LEFT_MID:
		return 5;
	case LV_ALIGN_OUT_BOTTOM_LEFT:
		return 5;
	case LV_ALIGN_OUT_BOTTOM_MID:
		return 0;
	case LV_ALIGN_OUT_BOTTOM_RIGHT:
		return 5;
	case LV_ALIGN_OUT_LEFT_BOTTOM:
		return 5;
	case LV_ALIGN_OUT_LEFT_MID:
		return 5;
	case LV_ALIGN_OUT_LEFT_TOP:
		return 5;
	case LV_ALIGN_OUT_RIGHT_BOTTOM:
		return 5;
	case LV_ALIGN_OUT_RIGHT_MID:
		return 5;
	case LV_ALIGN_OUT_RIGHT_TOP:
		return 5;
	case LV_ALIGN_OUT_TOP_LEFT:
		return 5;
	case LV_ALIGN_TOP_MID:
		return 0;
	case LV_ALIGN_OUT_TOP_RIGHT:
		return 5;
	default:
		return 0;
	}
}

int Utils::GetDY(lv_align_t align)
{
	switch (align)
	{
	case LV_ALIGN_DEFAULT:
		return 0;
	case LV_ALIGN_BOTTOM_LEFT:
		return 5;
	case LV_ALIGN_BOTTOM_MID:
		return 5;
	case LV_ALIGN_BOTTOM_RIGHT:
		return 5;
	case LV_ALIGN_CENTER:
		return 0;
	case LV_ALIGN_LEFT_MID:
		return 0;
	case LV_ALIGN_OUT_BOTTOM_LEFT:
		return 5;
	case LV_ALIGN_OUT_BOTTOM_MID:
		return 5;
	case LV_ALIGN_OUT_BOTTOM_RIGHT:
		return 5;
	case LV_ALIGN_OUT_LEFT_BOTTOM:
		return 5;
	case LV_ALIGN_OUT_LEFT_MID:
		return 0;
	case LV_ALIGN_OUT_LEFT_TOP:
		return 5;
	case LV_ALIGN_OUT_RIGHT_BOTTOM:
		return 0;
	case LV_ALIGN_OUT_RIGHT_MID:
		return 0;
	case LV_ALIGN_OUT_RIGHT_TOP:
		return 5;
	case LV_ALIGN_OUT_TOP_LEFT:
		return 5;
	case LV_ALIGN_TOP_MID:
		return 5;
	case LV_ALIGN_OUT_TOP_RIGHT:
		return 5;
	default:
		return 0;
	}
}