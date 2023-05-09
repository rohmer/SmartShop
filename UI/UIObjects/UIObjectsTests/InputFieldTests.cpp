#include <filesystem>
#include <string>
#include "../InputField.h"
#include "../../WindowManager.h"

#include "TestInitializer.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

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
	InputField *inputField = new InputField(lv_scr_act(), "Test String", InputField::E_STRING, "Test", 50, 50, 500, 60, 25);
	CHECK(std::strcmp(inputField->GetStringValue().c_str(), "Test String")==0);
	delete(inputField);
}

TEST(InputFields, EditStringInputField)
{
	InputField *inputField = new InputField(lv_scr_act(), "Test String", InputField::E_STRING, "Test", 50, 50, 500, 60, 25);
	delete(inputField);
}

TEST(InputFields, MultipleStringInputFields)
{
	InputField *inputField1 = new InputField(lv_scr_act(), "Test String 1", InputField::E_STRING, "Test", 50, 50, 500, 60, 25);
	InputField *inputField2 = new InputField(lv_scr_act(), "Test String 2", InputField::E_STRING, "Test", 50, 130, 500, 60, 25);

	delete(inputField1);
	delete(inputField2);
}

TEST(InputFields, MultilineString)
{
	InputField *inputField = new InputField(lv_scr_act(), "Test String 1", InputField::InputField::E_MULTI_STRING, "Test", 50, 50, 500, 30, 25);
	delete(inputField);
}

TEST(InputFields, IntegerField)
{
	InputField *inputField = new InputField(lv_scr_act(), "Test Integer 1", InputField::InputField::InputField::E_INTEGER, 123L, 50, 50, 500, 30, 8);
	//std::this_thread::sleep_for(std::chrono::seconds(30));
	delete(inputField);
}

TEST(InputFields, FloatField)
{
	InputField *inputField = new InputField(lv_scr_act(), "Test Float 1", InputField::InputField::InputField::E_FLOAT, 123L, 50, 50, 500, 30, 8);
	std::this_thread::sleep_for(std::chrono::seconds(30));
	delete(inputField);
}