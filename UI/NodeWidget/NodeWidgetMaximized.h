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
public:
	NodeWidgetMaximized(lv_obj_t *parentWindow, std::string CPUID);
	
	void Update();
	
	~NodeWidgetMaximized();
	void Close();
	
private:
	std::string cpuID;
	lv_obj_t *baseWindow = NULL, *parentWindow;
	lv_obj_t *drawSurface = NULL;
	static bool isOpen;
	
	lv_obj_t *topLeftPanel, *topCenterPanel, *topRightPanel, *topContainer;
	lv_obj_t *middleRowLeft, *middleRowRight, *middleContainer;
	lv_obj_t *bottomRow;		
	static void event_handler(lv_event_t *e);	
	void createObjects();
};