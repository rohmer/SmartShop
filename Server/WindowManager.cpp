#include "WindowManager.h"

lv_disp_draw_buf_t WindowManager::draw_buf_dsc;
lv_color_t WindowManager::buf[DISP_BUF_SIZE];
lv_disp_drv_t WindowManager::disp_drv;
lv_disp_draw_buf_t WindowManager::disp_buf;
lv_indev_drv_t WindowManager::indev_drv;

WindowManager::WindowManager()
{
	log = Logger::GetInstance();
}

void WindowManager::Init()
{
	lv_init();
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf, &buf, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf   = &disp_buf;
	disp_drv.flush_cb   = fbdev_flush;
	disp_drv.hor_res    = WIDTH;
	disp_drv.ver_res    = HEIGHT;
	lv_disp_drv_register(&disp_drv);
	
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = evdev_read;
	lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);
}