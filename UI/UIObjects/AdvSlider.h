#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <lvgl.h>

#include "InputField.h"

class AdvSlider
{
  public:
	enum eValuePos
	{
		NO_VALUE_POS,
		TOP_MID_VALUE_POS,
		LEFT_MID_VALUE_POS,
		BOTTOM_MID_VALUE_POS,
		RIGHT_MID_VALUE_POS
	};

	AdvSlider(
		lv_obj_t *parent,
		lv_area_t size,
		float &value,
		float max,
		float min,
		eValuePos valuePos = eValuePos::RIGHT_MID_VALUE_POS,
		bool valueEditable = true,
		float step = 0);
	AdvSlider(
		lv_obj_t *parent,
		lv_area_t size,
		long &value,
		long max,
		long min,
		eValuePos valuePos = eValuePos::RIGHT_MID_VALUE_POS,
		bool valueEditable = true,
		long step = 0);

	float GetFloatValue();
	void SetFloatValue(float val);
	long GetLongValue();
	void SetFloatValue(long val);

	void SetFloatExtents(float min, float max);
	float GetFloatMin();
	float GetFloatMax();
	
	void SetLongExtents(long min, long max);
	long GetLongMin();
	long GetLongMax();
	void SetFloatStep(float step);
	void SetLongStep(long step);

	void SetValuePosition(eValuePos valuePosition);
	eValuePos GetValuePosition();

	bool GetValueEditable();
	void SetValueEditable(bool val);

  private:
	enum eSliderType
	{
		LONG_SLIDER,
		FLOAT_SLIDER
	}; 
	void draw(lv_obj_t *parent);
	void recomputeSlider();
	void createValue();
	void setValue();
	lv_obj_t *container, *sliderObj = NULL, *valueObj = NULL;
	float fVal, fMin, fMax;
	long lVal, lMin, lMax;
	float fStep;
	long lStep;
	bool valueEditable;
	eSliderType sliderType;
	uint numSteps;
	eValuePos valuePos;
	lv_area_t size;
	std::shared_ptr<InputField> inputField;
};