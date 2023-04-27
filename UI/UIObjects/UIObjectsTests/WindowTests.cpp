#include "WindowTests.h"

void setupDisplay2()
{
	if (init2)
		return;
	init2 = true;
	lv_init();
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf1, &buf1, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv1);
	disp_drv1.draw_buf   = &disp_buf1;
	disp_drv1.flush_cb   = fbdev_flush;
	disp_drv1.hor_res    = WIDTH;
	disp_drv1.ver_res    = HEIGHT;
	lv_disp_drv_register(&disp_drv1);
	lv_disp_drv_register(&disp_drv1);
	
	//evdev_init();
	lv_indev_drv_init(&indev_drv1);
	indev_drv1.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv1.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv1);
	
	runner2 = new std::thread(tickThread2);
	shutdown2 = false;	
}

void tickThread2()
{
	while (!shutdown2)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}
}

TEST_GROUP(CollapsableWindowTests)
{
};

TEST(CollapsableWindowTests, CreateWindowTest)
{
	setupDisplay2();
	CollapsableWindow *cw = new CollapsableWindow(lv_scr_act(), "Big Test Window");
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
