#pragma once

#include <cmath>
#include <sstream>
#include <string>
#include <lvgl.h>

template<typename T>
class SpinBox
{
public:
  enum ESpinBoxLabelPOS
  {
	  E_ABOVE,
	  E_BELOW,
	  E_LEFT,
	  E_RIGHT
  };

  SpinBox(lv_obj_t *parent,
		  T maxValue,
		  T minValue,
		  T value,
		  T stepValue,
		  bool rollOver = true,
		  unsigned int integerPlaces = 3,
		  unsigned int decimalPlaces = 0) : value(value),
											minValue(minValue),
											stepValue(stepValue),
											rollOver(rollOver),
											intPlaces(integerPlaces),
											decPlaces(decPlaces)

  {
	  if (!std::is_arithmetic<T>::value)
	  {
		  throw "Spinbox must be an arithemtic value";
	  }
	  createObjects(parent);
  }

  ~SpinBox()
  {
	  if (spinBox != NULL)
		  lv_obj_del(spinBox);
	  if (labelObj != NULL)
		  lv_obj_del(labelObj);
	  if (incButton != NULL)
		  lv_obj_del(incButton);
	  if (decButton != NULL)
		  lv_obj_del(decButton);
  }

  float GetFloatValue();
  int GetIntValue();

private:
	lv_obj_t* spinBox = nullptr, * labelObj = nullptr, * incButton = nullptr, * decButton = nullptr;
	unsigned int decimalPlaces;
	T minValue, value, maxValue, stepValue;
	bool rollOver;
	uint intPlaces, decPlaces;
	ESpinBoxLabelPOS labelPos;
	std::string label;

	void createObjects(lv_obj_t *parent)
	{
		spinBox = lv_spinbox_create(parent);
		lv_spinbox_set_range(spinBox, (long)minValue, (long)maxValue);
		lv_spinbox_set_digit_format(spinBox, intPlaces - 1, decPlaces);
	}
	static void spinBoxIncrement(lv_event_t *event);
	static void spinBoxDecrement(lv_event_t *event);
};
