#include <filesystem>
#include <string>
#include "../../WindowManager.h"

#include "TestInitializer.h"
#include "../InputField.h"
#include "../AdvSlider.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

#ifndef DISABLE_SLIDER_TESTS
TEST_GROUP(AdvSliderTests)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
		lv_obj_clean(lv_scr_act());
	}
};

TEST(AdvSliderTests, CreateSliderLongEditable)
{
	long value = 22;
	AdvSlider<long> *slider = new AdvSlider<long>(lv_scr_act(), 200,20, &value, 0, 100, AdvSlider<long>::RIGHT_MID_VALUE_POS, true);
	slider->SetPos(100, 100);
 	std::this_thread::sleep_for(std::chrono::seconds(30));
}

TEST(AdvSliderTests, CrateSliderFloatEditable)
{
	float value = 22.0;
	AdvSlider<float> *slider = new AdvSlider<float>(lv_scr_act(), 200, 20, &value, 0.5, 77.2, AdvSlider<float>::RIGHT_MID_VALUE_POS, true);
	slider->SetPos(100, 100);
	std::this_thread::sleep_for(std::chrono::seconds(30));
}
#endif