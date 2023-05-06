#pragma once

#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>

#include <indev/evdev.h>
#include <display/fbdev.h>
#include <lvgl.h>
#include "../../Settings.h"

class TestInitializer
{
public:
	static TestInitializer *GetInstance();
	void InitializeInstance();
	
private:
	static TestInitializer *instance;
	TestInitializer();
	
	bool init = false;
	static lv_disp_draw_buf_t draw_buf_dsc;
	static lv_disp_drv_t disp_drv; 
	static lv_color_t buf[], buf2[];
	static lv_disp_draw_buf_t disp_buf;
	static lv_indev_drv_t indev_drv;
	std::thread *runner;
	bool done = false;
	void tickThread();
	
};