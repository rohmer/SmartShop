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

lv_area_t Area::CombineArea(lv_area_t a1, lv_area_t a2)
{
	lv_coord_t x1, y1, x2, y2;
	x1 = std::min(a1.x1, a2.x1);
	y1 = std::min(a1.y1, a2.y1);
	x2 = std::max(a1.x2, a2.x2);
	y2 = std::max(a1.y2, a2.y2);

	lv_area_t ret = {x1, y1, x2, y2};
	return ret;
}