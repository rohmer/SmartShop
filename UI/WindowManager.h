#pragma once

#include <dlfcn.h>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <lvgl.h>
#include <sdl/sdl_gpu.h>
#include <sdl/sdl.h>
#include <indev/evdev.h>
#include "../Logger/Logger.h"
#include "Settings.h"
#include "MainWindow.h"
#include "UIWidget/UIWidget.h"
#include "NodeWidgetManager.h"
#include "PluginManager.h"
#include "../DB/DB.h"

class WindowManager
{
public:
	static WindowManager *GetInstance();
	void Init();
	~WindowManager();
	
	bool LoadFont(std::string fontName, uint8_t fontSize, std::string filename);
	lv_font_t* GetFont(std::string fontName, uint8_t fontSize);
	void OnEvent(SensorEvent se);
	
private:
	WindowManager();
	static WindowManager *instance;
	static lv_disp_draw_buf_t draw_buf_dsc;
	static lv_disp_drv_t disp_drv; 
	static lv_color_t buf[];
	static lv_disp_draw_buf_t disp_buf;
	static lv_indev_drv_t indev_drv;
	
	void getActiveEventTypes();
	void initalizePlugins();
	
	Logger *log;
	bool shutdown = false;
	std::thread *runner, *managerThread;
	
	void tickThread();
	MainWindow *mainWindow;
	std::map<std::pair<std::string,uint8_t>, lv_font_t*>loadedFonts;
		

	uint nodeObjectsDrawn = 0;
	
	uint widgetWidth, widgetHeight;
	PluginManager *pluginManager;

	std::map<std::string, std::vector<DLClass<UIWidget> *>> eventToPlugin;
};