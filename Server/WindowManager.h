#pragma once

#include <lvgl/lvgl.h>
#include <display/fbdev.h>
#include <indev/evdev.h>

#include "../Logger/Logger.h"

#define WIDTH 800
#define HEIGHT 480
#define DISP_BUF_SIZE 256*1024

class WindowManager
{
public:
	WindowManager();
	void Init();
	
private:
	static lv_disp_draw_buf_t draw_buf_dsc;
	static lv_disp_drv_t disp_drv; 
	static lv_color_t buf[];
	static lv_disp_draw_buf_t disp_buf;
	static lv_indev_drv_t indev_drv;
	
	Logger *log;
};