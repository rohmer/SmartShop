#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

#include <lvgl.h>

#include "../DB/DB.h"
#include "../Logger/LogMsg.h"
#include "Settings.h"

class LogTable
{
public:
	LogTable(lv_obj_t *tabView, lv_obj_t *logTab);
	
	void Refresh();
private:
	lv_obj_t *tableObject = NULL, *tabView, *logTab;
	
	static void draw_part_event_cb(lv_event_t *);
};