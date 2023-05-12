#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <lvgl.h>

#include "InputField.h"

template <class T>
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

	/**
	 * Creates a slider object
	 * @param parent - The parent of the slider object 
	 * @param width - The width of the slider (To get the total size of the object @see GetSize() )
	 * @param height - The height of the slider (To get the total size of the object @see GetSize() )
	 * @param value - The value of this object, must be arithmetic
	 * @param minValue - The minimum value 
	 * @param maxValue - The maximum value
	 * @param valueIsEditable - If try an @see InputField() will be created for the object, otherwise a label will
	 * @param stepSize - By default, the steps will be the width of the slider/2, each step will be that much of the object
	 *					 If step size is set, each step will be that big.  Note, if you set it too small, the slider will have issues
	 *					 computing
	 **/
	AdvSlider(lv_obj_t *parent,
			  lv_coord_t width,
			  lv_coord_t height,
			  T *value,
			  T minValue,
			  T maxValue,
			  eValuePos valuePostion = RIGHT_MID_VALUE_POS,
			  bool valueIsEditable = true,
			  T stepSize = 0,
			  uint16_t numSteps = 0) : value(value),
									   minValue(minValue),
									   maxValue(maxValue),
									   valuePos(valuePostion),
									   valueIsEditable(valueIsEditable),
									   stepSize(stepSize),
									   numSteps(numSteps)
	{
		if (!std::is_arithmetic<T>())
		{
			throw "Value class must be arithmetic type";
		}

		createObjects(parent, width, height);
	}

	~AdvSlider<T>()
	{
		if (inputField != NULL)
			delete (inputField);
		if (sliderObj != NULL)
			lv_del_obj(sliderObj);
	}

	void SetDecimalPrecision(uint8_t value)
	{
		decimalPlaces = value;
	}

	uint8_t GetDecimalPrecision()
	{
		return decimalPlaces;
	}
	
	void SetPos(lv_coord_t x, lv_coord_t y)
	{
		if (sliderObj == NULL)
			return;
		lv_obj_set_pos(sliderObj, x, y);
		if (valueIsEditable)
		{
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}
		}
		else if(labelObj!=NULL)
		{
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}
		}
	}

	void SetValuePos(eValuePos position)
	{
		if (valuePos == position)
			return;
		valuePos = position;
		if (position == AdvSlider::NO_VALUE_POS)
		{
			if (valueIsEditable && inputField != NULL)
			{
				delete (inputField);
			}
			if (!valueIsEditable && valueLabel != NULL)
			{
				lv_obj_del(valueLabel);
			}
			return;
		}
		if (valueIsEditable && inputField != NULL)
		{
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}
			return;
		}
		if (labelObj != NULL)
		{
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}
		}
	}

	void SetValue(T newValue)
	{
		if (std::is_integral<T>::value)
		{

			// We can just set the value and move on
			if (sliderObj != NULL)
			{
				lv_obj_remove_event_cb(sliderObj, slider_position_changed_event_cb);
				lv_slider_set_value(sliderObj, newValue, LV_ANIM_ON);
				lv_obj_add_event_cb(sliderObj, slider_position_changed_event_cb, LV_EVENT_VALUE_CHANGED,this);
			}
			if (inputField != NULL)
			{
				lv_obj_remove_event_cb(inputField->GetObject(), value_changed_event_cb);				
				inputField->SetValue(newValue);
				lv_obj_add_event_cb(inputField->GetObject(), value_changed_event_cb, LV_EVENT_VALUE_CHANGED, this);
			}
			value = &newValue;
			return;
		}

		// Float is a little harder, the slider only stores where we are between min and max based on numSteps and stepValue
		if (inputField != NULL)
		{
			lv_obj_remove_event_cb(inputField->GetObject(), value_changed_event_cb);
			T n = std::pow(10.0f, decimalPlaces);
			T v = newValue * stepSize;
			v = std::round(v * n) / n;
			inputField->SetValue(v);
			lv_obj_add_event_cb(inputField->GetObject(), value_changed_event_cb, LV_EVENT_VALUE_CHANGED, this);
		}

		if (sliderObj != NULL)
		{
			lv_obj_remove_event_cb(sliderObj, slider_position_changed_event_cb);
			lv_slider_set_value(sliderObj, newValue, LV_ANIM_ON);
			lv_obj_add_event_cb(sliderObj, slider_position_changed_event_cb, LV_EVENT_VALUE_CHANGED, this);
		}
		value = &newValue;
	}
	
	T GetValue()
	{
		return *value;
	}
	
	void SetExtents(T minValue, T maxValue)
	{
		if (minValue <= maxValue)
		{
			this->minValue = minValue;
			this->maxValue = maxValue;
		}
		else
		{
			this->minValue = maxValue;
			this->maxValue = minValue;
		}
		if (value < minValue)
			value = minValue;
		if (value > maxValue)
			value = maxValue;
		recomputeSlider();
	}

	void SetValueLabelWidth(lv_coord_t width)
	{
		if (inputField != NULL)
		{
			inputField->SetWidth(width);
			return;
		}
		if (labelObj != NULL)
			lv_obj_set_width(labelObj, width);
	}

	void SetValueLabelHeight(lv_coord_t height)
	{
		if (inputField != NULL)
		{
			inputField->SetHeight(height);
			return;
		}
		if (labelObj != NULL)
			lv_obj_set_height(labelObj, height);
	}

	lv_area_t GetSize()
	{
		lv_area_t ret;
		if (sliderObj == NULL)
			return ret;
		lv_obj_get_coords(sliderObj, &ret);
		if (inputField != NULL)
		{
			ret = Area::CombineArea(inputField->GetArea(), ret);
		}
		return ret;
	}

	lv_coord_t GetWidth()
	{
		lv_area_t size = GetSize();
		return size.x2 - size.x1;
	}

	lv_coord_t GetHeight()
	{
		lv_area_t size = GetSize();
		return size.y2 - size.y1;
	}

	lv_obj_t *GetSlider()
	{
		return sliderObj;
	}

  private:
	void createObjects(lv_obj_t *parent,lv_coord_t width, lv_coord_t height)
	{
		if (sliderObj != NULL)
			lv_obj_del(sliderObj);
		sliderObj = lv_slider_create(parent);
		lv_obj_set_size(sliderObj, width / 5 * 4, height);
		if (valuePos == AdvSlider::NO_VALUE_POS)
			return;
		if (valueIsEditable)
		{
			inputField = new InputField<T>(parent,
										   *value,
										   0,
										   0,
										   lv_font_default()->line_height * getValueSize(),
										   lv_font_default()->line_height + 3);
			if (!(minValue == 0 && maxValue == 0))
			{
				inputField->SetMinValue(minValue);
				inputField->SetMaxValue(maxValue);
			}
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):			
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(inputField->GetObject(), sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}

			lv_obj_add_event_cb(inputField->GetObject(), value_changed_event_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
		}
		else
		{
			if (labelObj == NULL)
				labelObj = lv_label_create(parent);
			std::stringstream ss;
			ss << value;
			lv_obj_set_size(labelObj,
							getValueSize() * lv_font_default()->line_height,
							lv_font_default()->line_height);
			lv_label_set_text(labelObj, ss.str().c_str());
			switch (valuePos)
			{
			case (TOP_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
				break;
			case (RIGHT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				break;
			case (LEFT_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				break;
			case (BOTTOM_MID_VALUE_POS):
				lv_obj_align_to(labelObj, sliderObj, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 3);
				break;
			}
		}
		if (numSteps == 0 && stepSize == 0)
		{
			// Both are set to 0, which is the default.  We will set the numSteps to the slider width/2
			numSteps = lv_obj_get_width(sliderObj) / 2;
			stepSize = (maxValue - minValue) / numSteps;
		}
		if (numSteps == 0 && stepSize != 0)
		{
			numSteps = (maxValue - minValue) / stepSize;
		}
		if (numSteps != 0)
		{
			stepSize = (maxValue - minValue) / numSteps;
		}
		if (std::is_floating_point<T>::value)
		{
			// The slider only accepts int32_t, so we need to convert that to a float.
			// We do this by computing the value by steps and step value
			// The range is 0->numSteps

			lv_slider_set_range(sliderObj, 0, numSteps);
		}
		else		// Its an integral values, so we can use the slider's functionality
		{
			lv_slider_set_range(sliderObj, minValue, maxValue);
			
		}

		SetValue(*value);

		lv_obj_add_event_cb(sliderObj, slider_position_changed_event_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
	}

	T GetStepSize()
	{
		return stepSize;
	}

	void SetStepSize(T stepSize)
	{
		this->stepSize = stepSize;
	}

	uint GetNumSteps()
	{
		return numSteps;
	}

	void SetNumSteps(uint val)
	{
		if (numSteps > 1)
			numSteps = val;
		else
			numSteps = 2;
	}
	
	void
	recomputeSlider()
	{
		SetValue(value);
	}

	uint getValueSize()
	{
		T maxV = std::max(abs(maxValue), abs(minValue));
		std::stringstream ss;
		ss << maxV;
		return ss.str().size();
	}

	static void value_changed_event_cb(lv_event_t *e)
	{
		lv_obj_t *obj = lv_event_get_target(e);
		AdvSlider<T> *aso = (AdvSlider<T> *)lv_event_get_user_data(e);
		if (aso->sliderChanged)
			return;
		// Avoid an endless loop
		if (aso->valueChanged)
		{
			aso->valueChanged = false;
			return;
		}
		aso->valueChanged = true;
		if (std::is_integral<T>::value)
		{
			aso->SetValue(aso->inputField->GetLongValue());
		}
		else
		{
			double v = aso->inputField->GetDoubleValue();
			aso->SetValue(v);
		}
	}
	
	static void slider_position_changed_event_cb(lv_event_t *e)
	{
		AdvSlider<T> *aso = (AdvSlider<T> *)lv_event_get_user_data(e);
		lv_obj_t *obj = lv_event_get_target(e);
		if (aso->sliderChanged)
		{
			aso->sliderChanged = false;
			return;
		}
		aso->sliderChanged = true;
		uint32_t v = lv_slider_get_value(obj);
		aso->SetValue(v);
	}

	T *value;
	T minValue;
	T maxValue;
	T stepSize;
	eValuePos valuePos;
	uint numSteps=0;

	uint8_t decimalPlaces = 2;
	bool valueIsEditable;
	lv_obj_t *labelObj = NULL, *sliderObj = NULL, *valueLabel=NULL;
	InputField<T> *inputField = NULL;
	bool sliderChanged = false, valueChanged=false;
};