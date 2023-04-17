#pragma once

#include <cmath>
#include <sstream>
#include <string>
#include <lvgl.h>

class SpinBox
{
public:
	enum ESpinBoxLabelPOS
	{
		E_ABOVE,
		E_LEFT
	};

	SpinBox(lv_obj_t *parent,
		int x,
		int y,
		int width,
		int maxValue, 
		int minValue, 
		int value, 
		int stepValue, 
		bool rollOver,
		unsigned int integerPlaces=3,
		unsigned int decimalPlaces=0,	
		ESpinBoxLabelPOS labelPos=ESpinBoxLabelPOS::E_ABOVE,
		std::string label="");
	
	~SpinBox();

	float GetFloatValue();
	int GetIntValue();

private:
	lv_obj_t* spinBox = nullptr, * label = nullptr, * incButton = nullptr, * decButton = nullptr;
	static void spinBoxIncrement(lv_event_t *event);
	static void spinBoxDecrement(lv_event_t *event);
	unsigned int decimalPlaces;
};
