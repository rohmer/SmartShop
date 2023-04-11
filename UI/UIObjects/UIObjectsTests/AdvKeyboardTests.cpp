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
TEST_GROUP(NGramSplit)
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

TEST(AdvKeyboard, TextPredictionBigram)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie")==true);
	std::multimap<float, std::string, std::greater<float>> results = advKeyboard.GetSuggestions("the do", 5);
	CHECK(results.size() > 0);
	for (std::multimap<float, std::string, std::greater<float>>::iterator it = results.begin(); it != results.end(); ++it)
		std::cout << it->second << "\t" << it->first << "\n";
}

TEST(AdvKeyboard, TextPredictionTrigram)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::multimap<float, std::string, std::greater<float>> results = advKeyboard.GetSuggestions("the dogs ru", 5);
	CHECK(results.size() > 0);
	for (std::multimap<float, std::string, std::greater<float>>::iterator it = results.begin(); it != results.end(); ++it)
		std::cout << it->second << "\t" << it->first << "\n";
}

TEST(NGramSplit, GetNGramsUnigramSimple)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("Cali");
	CHECK_EQUAL(strcmp(grams[0].c_str(), "Cali"),0);
	CHECK_EQUAL(grams[1].length(), 0);
	CHECK_EQUAL(grams[2].length(), 0);
}

TEST(NGramSplit, GetNGramsUnigramWithTerminator)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("This is a test. Cali");
	CHECK_EQUAL(strcmp(grams[0].c_str(), "Cali"), 0);
	CHECK_EQUAL(grams[1].length(), 0);
	CHECK_EQUAL(grams[2].length(), 0);
}

TEST(NGramSplit, GetNGramsUnigramWithTrailingSpace)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("This is a test. Cali ");
	CHECK_EQUAL(strcmp(grams[0].c_str(), "Cali"), 0);
	CHECK_EQUAL(grams[1].length(), 0);
	CHECK_EQUAL(grams.size(), 2);;
}

TEST(NGramSplit, CheckBigramSimple)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("Great Cali");
	if (strcmp(grams[1].c_str(), "Cali") != 0)
	{
		std::stringstream ss;
		ss << "Expected grams[1]=='Cali', received: '" << grams[1]<<"'";
		FAIL(ss.str().c_str());
	}
	if (strcmp(grams[0].c_str(), "Great") != 0)
	{
		std::stringstream ss;
		ss << "Expected grams[0]=='Great', received: '" << grams[0]<<"'";
		FAIL(ss.str().c_str());
	}
	CHECK_EQUAL(grams[2].length(), 0);
}

TEST(NGramSplit, CheckBigramSimpleWithSpace)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("Great Cali" );
	CHECK_EQUAL(strcmp(grams[1].c_str(), "Cali"), 0);
	CHECK_EQUAL(strcmp(grams[0].c_str(), "Great"), 0);
}

TEST(NGramSplit, CheckBigramSpaceAndSeperator)
{
	AdvKeyboard advKeyboard(false);
	CHECK(advKeyboard.LoadDictionary("dict.trie") == true);
	std::vector<std::string> grams = advKeyboard.GetNGrams("It was.  Great Cali ");
	CHECK_EQUAL(strcmp(grams[1].c_str(), "Cali"), 0);
	CHECK_EQUAL(strcmp(grams[0].c_str(), "Great"), 0);
	CHECK_EQUAL(grams.size(), 2);
}


TEST(NGramSplit, TrigramSimple)
{
	
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
