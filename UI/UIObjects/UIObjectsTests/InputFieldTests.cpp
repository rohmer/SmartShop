#include "InputFieldTests.h"

/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

bool init = false;
TEST_GROUP(InputFieldTests)
{	
};

void setupDisplay()
{
	if (init)
		return;
	init = true;
	lv_init();
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf, &buf, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf   = &disp_buf;
	disp_drv.flush_cb   = fbdev_flush;
	disp_drv.hor_res    = WIDTH;
	disp_drv.ver_res    = HEIGHT;
	lv_disp_drv_register(&disp_drv);
	lv_disp_drv_register(&disp_drv);
	
	evdev_init();
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv);
	
	runner = new std::thread(tickThread);
	shutdown = false;	
}

void tickThread()
{
	while (!shutdown)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}
}

TEST(InputFieldTests, CreateStringInputInitializer)
{
	setupDisplay();
	InputField strInputField(lv_scr_act(), "CreateStringInputInitializer", InputField::E_STRING, "Value", 200, 200, 300, 60, 100);
	
	std::this_thread::sleep_for(std::chrono::seconds(1));
	shutdown = true;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
}

