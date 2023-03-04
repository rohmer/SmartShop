#pragma once

#include <iomanip>
#include <string>
#include <ctime>
#include <lvgl.h>
#include "Settings.h"
#include "../NetworkTools/NetworkTools.h"
#include "LogTable.h"

class MainWindow
{
public:
	MainWindow();
	
private:
	lv_obj_t *windowObj;
	lv_obj_t *appTitle;
	static lv_obj_t *wifiStrIcon, *wifiNetworkLabel;
	
	static lv_obj_t *timeString;
	
	static void updateWinTask(lv_timer_t *timer);
	static int wifiUpdateTimer, logUpdateTimer;
	lv_timer_t *updateTimer;
	
	lv_obj_t *tabView, *nodeTab, *eventTab;
	static lv_obj_t *logTab; 
	
	static LogTable *logTable;
};