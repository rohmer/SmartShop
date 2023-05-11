#pragma once

#include <algorithm>
#include <lvgl.h>

class Area
{
  public:
	static bool OnScreen(lv_area_t area, lv_point_t topLeftCorner);
	static lv_area_t CombineArea(lv_area_t a1, lv_area_t a2);
};