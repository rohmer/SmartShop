#pragma once

#include <lvgl.h>
#include <display/fbdev.h>
#include <indev/evdev.h>

#include "../InputField.h"

#include <thread>
#include <unistd.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>


#ifndef WIDTH
#define WIDTH	1920
#endif

#ifndef HEIGHT
#define HEIGHT	1080
#endif

#ifndef DISP_BUF_SIZE
#define DISP_BUF_SIZE	256*1024
#endif

// NODE DISPLAY SETTING
#ifndef NODE_COLUMNS
#define NODE_COLUMNS	 3
#endif
#ifndef NODE_ROWS
#define NODE_ROWS	3
#endif 


static lv_disp_draw_buf_t draw_buf_dsc;
static lv_disp_drv_t disp_drv; 
static lv_color_t buf[DISP_BUF_SIZE];
static lv_disp_draw_buf_t disp_buf;
static lv_indev_drv_t indev_drv;

std::thread *runner;

bool shutdown = false;
void tickThread();