#pragma once

#include <dlfcn.h>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <thread>

#include <lvgl.h>
#include <display/fbdev.h>
#include <indev/evdev.h>

#include "../Logger/Logger.h"
#include "Settings.h"
#include "MainWindow.h"
#include "UIWidget/UIWidget.h"
#include "dlclass.hpp"

class WindowManager
{
public:
	static WindowManager *GetInstance();
	void Init();
	~WindowManager();
	
	bool LoadFont(std::string fontName, uint8_t fontSize, std::string filename);
	lv_font_t* GetFont(std::string fontName, uint8_t fontSize);
	
	static void WidgetCallback(lv_event_t *event);
	void LoadWidgets();

private:
	WindowManager();
	static WindowManager *instance;
	static lv_disp_draw_buf_t draw_buf_dsc;
	static lv_disp_drv_t disp_drv; 
	static lv_color_t buf[];
	static lv_disp_draw_buf_t disp_buf;
	static lv_indev_drv_t indev_drv;
	
	Logger *log;
	bool shutdown = false;
	std::thread *runner;
	
	void tickThread();
	
	MainWindow *mainWindow;
	std::map<std::pair<std::string,uint8_t>, lv_font_t*>loadedFonts;
	
	struct sWidgets
	{
	public:
		std::shared_ptr<UIWidget> widget;
		bool isMaximized = false;
		std::vector<std::string> dataPoints;
		std::string Name;
	};
	
	std::map<int, sWidgets> widgets;
};