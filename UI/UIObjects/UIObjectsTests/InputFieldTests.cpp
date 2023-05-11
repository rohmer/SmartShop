#include <filesystem>
#include <string>
#include "../InputField.h"
#include "../../WindowManager.h"

#include "TestInitializer.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>


#ifndef DISABLE_INPUT_TESTS
TEST_GROUP(InputFields)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
		lv_obj_clean(lv_scr_act());
	}
};

TEST(InputFields, StringInputField)
{
	InputField<std::string> *inputField = new ::InputField<std::string>(lv_scr_act(), "Test String", 50,50,200,50);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::string value = inputField->GetStringValue();
	CHECK(std::strcmp(value.c_str(), "Test String")==0);
	delete(inputField);
}

TEST(InputFields, MultipleStringInputFields)
{
	InputField<std::string> *InputField1 = new InputField<std::string>(lv_scr_act(), "Test String 1", 50, 50, 500, 60);
	InputField1->SetLabel("Test 1");
	InputField<std::string> *InputField2 = new InputField<std::string>(lv_scr_act(), "Test String 2", 100, 150, 500, 60);
	InputField2->SetLabel("Test 2");
	delete(InputField1);
	delete(InputField2);
}

TEST(InputFields, MultilineString)
{
	InputField<std::string> *input = new InputField<std::string>(lv_scr_act(), "Test String 1", 50, 50, 500, 100);
	input->SetStringMultiline(true);
	delete(input);
}

TEST(InputFields, IntegerField)
{
	InputField<int> *input = new InputField<int>(lv_scr_act(), 123, 50, 50, 500, 100);
	//std::this_thread::sleep_for(std::chrono::seconds(30));
	delete(input);
}

TEST(InputFields, LongField)
{
	InputField<long> *input = new InputField<long>(lv_scr_act(), 123L, 50, 50, 500, 30);
	delete(input);
}

TEST(InputFields, FloatField)
{
	InputField<float> *input = new InputField<float>(lv_scr_act(), 123.0f, 50, 50, 500, 100);
	//std::this_thread::sleep_for(std::chrono::seconds(30));
	delete(input);
}

TEST(InputFields, DoubleField)
{
	InputField<double> *input = new InputField<double>(lv_scr_act(), 123.1, 50, 50, 500, 30);
	delete(input);
}


#endif