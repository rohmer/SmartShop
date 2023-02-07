#pragma once

// An example widget that does a lot of different things a widget can do

#include <time.h>
#include <string>

#include <lvgl.h>

#include "../UIWidget/UIWidget.h"

extern "C" UIWidget * Factory();

class StatusWidget: public UIWidget
{
public:
	StatusWidget() :
		UIWidget("ALL", "Status")
	{
	}
	
	void Init() override;
	
	void Draw(lv_obj_t* parent, uint16_t width, uint16_t height, uint16_t x, uint16_t y) override;

private:
	void createObjects(lv_obj_t *parent);
};