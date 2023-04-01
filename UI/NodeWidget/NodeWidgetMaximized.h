#pragma once
#include <unistd.h>

#include <lvgl.h>
#include "../../DB/DB.h"
#include "../../Logger/LogMsg.h"
#include "../../SensorEvent/SensorEvent.h"
#include "../UIWidget/UIWidget.h"
#include "sqlite_orm.h"

class NodeWidgetMaximized
{
	NodeWidgetMaximized(lv_obj_t *parentWindow, std::string CPUID);
	
	void Update();
	
	~NodeWidgetMaximized();
	
private:
	std::string cpuID;
	lv_obj_t *baseWindow = NULL;
	lv_obj_t *drawSurface = NULL;
	static bool isOpen;
	
	static void event_handler(lv_event_t *e);
};