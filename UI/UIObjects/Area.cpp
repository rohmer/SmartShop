#include "Area.h"

bool Area::OnScreen(lv_area_t area, lv_point_t topLeft)
{
	uint16_t width = area.x2 - area.x1;
	uint16_t height = area.y2 - area.y1;

	area.x1 = topLeft.x;
	area.y1 = topLeft.y;
	area.x2 = area.x1 + width;
	area.y2 = area.y1 + height;

	if (area.x1 < 0)
		return false;
	if (area.y1 < 0)
		return false;
	if (area.x2 > lv_scr_act()->coords.x2)
		return false;
	if (area.y2 > lv_scr_act()->coords.y2)
		return false;
	return true;
}