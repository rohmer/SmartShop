#pragma once

#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <lvgl.h>

#include "Area.h"

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

	enum eKBPreferredLocation
	{
		KB_LEFT=0,
		KB_RIGHT=1,
		KB_TOP=2,
		KB_BOTTOM=3,
		NONE=4
	};
	InputField(
		lv_obj_t *parent, 
		std::string label, 
		eInputType inputType, 
		std::string value, 
		uint x, 
		uint y, 
		uint width, 
		uint height, 
		int maxSize, 
		eKBPreferredLocation prefKBLoc=KB_BOTTOM);
	
	InputField(
		lv_obj_t *parent, 
		std::string label, 
		eInputType inputType, 
		double value, 
		uint x, 
		uint y, 
		uint width, 
		uint height,
		int maxSize, 
		double minValue=std::numeric_limits<double>::min(), 
		double maxValue=std::numeric_limits<double>::max(),
		eKBPreferredLocation prefKBLoc=KB_BOTTOM);

	InputField(
		lv_obj_t *parent,
		std::string label,
		eInputType inputType,
		int value,
		uint x,
		uint y,
		uint width,
		uint height,
		int maxSize,
		int minValue = std::numeric_limits<int>::min(),
		int maxValue = std::numeric_limits<int>::max(),
		eKBPreferredLocation prefKBLoc=KB_BOTTOM);

	InputField(
		lv_obj_t *parent,
		std::string label,
		eInputType inputType,
		long value,
		uint x,
		uint y,
		uint width,
		uint height,
		int maxSize,
		long minValue = std::numeric_limits<long>::min(),
		long maxValue = std::numeric_limits<long>::max(),
		eKBPreferredLocation prefKBLoc = KB_BOTTOM);
	InputField(
		lv_obj_t *parent,
		std::string label,
		eInputType inputType,
		float value,
		uint x,
		uint y,
		uint width,
		uint height,
		int maxSize,
		float minValue = std::numeric_limits<float>::min(),
		float maxValue = std::numeric_limits<float>::max(),
		eKBPreferredLocation prefKBLoc = KB_BOTTOM);
	
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
	lv_area_t GetArea();
	

  private:
	eInputType inputType;
	int maxSize, iMinValue, iMaxValue;
	float fMinValue, fMaxValue;
	uint x, y, width, height;
	lv_obj_t *parent;

	lv_obj_t *textArea = NULL, *taLabel = NULL, *keyboard = NULL, *errMsg = NULL;
	eKBPreferredLocation prefLoc;
	static void textArea_valueChanged(lv_event_t *e);
	static void textArea_clicked(lv_event_t *e);
	static void keyboard_btn_handler(lv_event_t *e);
	void setKBLocation();
	
	void createObjects(std::string value, std::string label);
	void createKeyboard();
};