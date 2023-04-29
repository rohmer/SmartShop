#include "TestInitializer.h"

TestInitializer *TestInitializer::instance = NULL;
lv_disp_draw_buf_t TestInitializer::draw_buf_dsc;
lv_color_t TestInitializer::buf[DISP_BUF_SIZE];
lv_color_t TestInitializer::buf2[DISP_BUF_SIZE];
lv_disp_drv_t TestInitializer::disp_drv;
lv_disp_draw_buf_t TestInitializer::disp_buf;
lv_indev_drv_t TestInitializer::indev_drv;

TestInitializer *TestInitializer::GetInstance()
{
	if (instance == NULL)
		instance = new TestInitializer();
	return instance;
}

TestInitializer::TestInitializer()
{
}

void TestInitializer::InitializeInstance()
{	
	lv_init();
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf, &buf, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = fbdev_flush;
	disp_drv.hor_res = WIDTH;
	disp_drv.ver_res = HEIGHT;
	lv_disp_drv_register(&disp_drv);

	evdev_init();
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv);
	runner = new std::thread([this]{tickThread(); });
}

void TestInitializer::tickThread()
{
	while (!done)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}
}