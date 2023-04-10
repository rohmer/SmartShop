#include "AdvKeyboardTests.h"

/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

bool init1 = false;
TEST_GROUP(AdvKeyboard)
{	
}
;

void setupDisplay()
{
	if (init1)
		return;
	init1 = true;
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
	
	evdev_init();
	lv_indev_drv_init(&indev_drv1);
	indev_drv1.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv1.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv1);
	
	runner1 = new std::thread(tickThread1);
	shutdown1 = false;	
}

void tickThread1()
{
	while (!shutdown1)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}
}

TEST(AdvKeyboard, TextPrediction1)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie")==true);
	std::multimap<float, std::string, std::greater<float>> results = advKeyboard.GetSuggestions("dog", 3);
	CHECK(results.size() > 0);
	for (std::multimap<float, std::string, std::greater<float>>::iterator it = results.begin(); it != results.end(); ++it)
		std::cout << it->second << "\t" << it->first << "\n";
}
TEST(AdvKeyboard, CreateKeyboardWithDict)
{
	return;
	setupDisplay();
	lv_obj_t *textArea = lv_textarea_create(lv_scr_act());
	lv_obj_set_size(textArea, 500, 80);
	lv_obj_set_pos(textArea, 500, 400);
	AdvKeyboard AdvKeyboard(lv_scr_act(), textArea, AdvKeyboard::BELOW, "EN-US.dict");
	std::this_thread::sleep_for(std::chrono::seconds(30));
}
