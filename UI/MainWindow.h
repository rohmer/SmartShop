#pragma once

#include <iomanip>
#include <string>
#include <ctime>
#include <lvgl.h>
#include <thread>
#include "Settings.h"
#include "../NetworkTools/NetworkTools.h"
#include "LogTable.h"
#include "NodeWidgetManager.h"

class MainWindow
{
public:
	MainWindow(uint widgetWidth, uint widgetHeight);
	
private:
	lv_obj_t *windowObj;
	lv_obj_t *appTitle;
	static lv_obj_t *wifiStrIcon, *wifiNetworkLabel;
	
	static lv_obj_t *timeString;
	
	void updateWinTask();
	void updateNodeWidgets();
	
	static int wifiUpdateTimer, logUpdateTimer;
	std::thread *updateTimer;
	
	lv_obj_t *tabView, *nodeTab, *eventTab;
	static lv_obj_t *logTab; 
	
	static LogTable *logTable;
	uint widgetWidth, widgetHeight;
	bool shutdown = false;
	NodeWidgetManager nodeWidgetManager;
};