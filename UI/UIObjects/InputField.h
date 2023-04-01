#pragma once

#include <sstream>
#include <string>

#include <lvgl.h>

class InputField
{
  public:
	enum eInputType
	{
		E_INTEGER = 0,
		E_FLOAT =1,
		E_STRING = 2,
		E_MULTI_STRING = 3
	};

	InputField(lv_obj_t *parent, std::string label, eInputType inputType, std::string value, uint x, uint y, uint width, uint height, int maxSize);
	InputField(lv_obj_t *parent, std::string label, eInputType inputType, float value, uint x, uint y, uint width, uint height,int maxSize, float minValue, float maxValue);
	InputField(lv_obj_t *parent, std::string label, eInputType inputType, int value, uint x, uint y, uint width, uint height,int maxSize, int minValue, int maxValue);

	eInputType GetInputType() { return inputType; }
	lv_obj_t *GetTextArea() { return textArea; }
	int GetMinI() { return iMinValue; }
	int GetMaxI() { return iMaxValue; }
	float GetMinF() { return fMinValue; }
	float GetMaxF() { return fMaxValue; }

	lv_obj_t *GetKeyboard() { return keyboard; }
	void SetKeyboard(lv_obj_t *kb) { keyboard = kb; }

	std::string GetStringValue();
	int GetIntValue();
	float GetFloatValue();

  private:
	eInputType inputType;
	int maxSize, iMinValue, iMaxValue;
	float fMinValue, fMaxValue;
	uint x, y, width, height;
	lv_obj_t *parent;

	lv_obj_t *textArea, *keyboard = NULL;
	
	static void textArea_valueChanged(lv_event_t *e);
	static void textArea_clicked(lv_event_t *e);
	static void keyboard_btn_handler(lv_event_t *e);
};