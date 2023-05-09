#include "AdvSlider.h"

AdvSlider::AdvSlider(
	lv_obj_t *parent,
	lv_area_t size,
	float &value,
	float max,
	float min,
	eValuePos valuePos,
	bool valueEditable,
	float step) : size(size),
				  fVal(value),
				  lVal(0),
				  fMin(min),
				  fMax(max),
				  lMin(0),
				  lMax(0),
				  fStep(step),
				  lStep(0),
				  valueEditable(valueEditable),
				  sliderType(eSliderType::FLOAT_SLIDER),
				  valuePos(valuePos)
{
	draw(parent);
}

AdvSlider::AdvSlider(
	lv_obj_t *parent,
	lv_area_t size,
	long &value,
	long max,
	long min,
	eValuePos valuePos,
	bool valueEditable,
	long step) : size(size),
				 fVal(value),
				 lVal(0),
				 fMin(0),
				 fMax(0),
				 lMin(min),
				 lMax(max),
				 lStep(step),
				 fStep(0),
				 valueEditable(valueEditable),
				 sliderType(eSliderType::LONG_SLIDER),
				 valuePos(valuePos)
{
	draw(parent);
}

float AdvSlider::GetFloatValue()
{
	return fVal;
}

float AdvSlider::GetFloatMax()
{
	return fMax;
}

float AdvSlider::GetFloatMin()
{
	return fMin;
}

void AdvSlider::SetFloatExtents(float min, float max)
{
	if (fMin < fMax)
	{
		fMin = min;
		fMax = max;
	}
	else
	{
		fMin = max;
		fMax = min;
	}

	if (sliderType == AdvSlider::FLOAT_SLIDER)
		recomputeSlider();
}

void AdvSlider::SetLongExtents(long min, long max)
{
	if (min < max)
	{
		lMin = min;
		lMax = max;
	}
	else
	{
		lMin = min;
		lMax = max;
	}
	if (sliderType == AdvSlider::LONG_SLIDER)
		recomputeSlider();
}

long AdvSlider::GetLongMax()
{
	return lMax;
}

long AdvSlider::GetLongMin()
{
	return lMin;
}

long AdvSlider::GetLongValue()
{
	return lVal;
}

void AdvSlider::SetFloatStep(float val)
{
	if (val != 0)
	{
		numSteps = (fMax - fMin) / val;
		recomputeSlider();
	}
}

void AdvSlider::SetLongStep(long val)
{
	if (val != 0)
	{
		numSteps = (lMax - lMin) / val;
		recomputeSlider();
	}
}

void AdvSlider::SetValuePosition(eValuePos val)
{
	if (val == valuePos)
		return;
	if (val == AdvSlider::NO_VALUE_POS)
	{
		if (valueObj != NULL)
			lv_obj_add_flag(valueObj, LV_OBJ_FLAG_HIDDEN);
		return;
	}
	if (valuePos == AdvSlider::NO_VALUE_POS)
	{
		// Was hidden, now visable
		if (valueObj != NULL)
			lv_obj_clear_flag(valueObj, LV_OBJ_FLAG_HIDDEN);
	}
	if (valueObj == NULL)
		createValue();
	valuePos = val;
	switch (valuePos)
	{
	case AdvSlider::NO_VALUE_POS:
		break;
	case AdvSlider::TOP_MID_VALUE_POS:
		lv_obj_align_to(valueObj, sliderObj, LV_ALIGN_OUT_TOP_MID, 0, -3);
		break;
	case AdvSlider::LEFT_MID_VALUE_POS:
		lv_obj_align_to(valueObj, sliderObj, LV_ALIGN_LEFT_MID, -3, 0);
		break;
	case AdvSlider::BOTTOM_MID_VALUE_POS:
		lv_obj_align_to(valueObj, sliderObj, LV_ALIGN_BOTTOM_MID, 0, 3);
		break;
	case AdvSlider::RIGHT_MID_VALUE_POS:
		lv_obj_align_to(valueObj, sliderObj, LV_ALIGN_RIGHT_MID, 3, 0);
		break;
	}
}

AdvSlider::eValuePos AdvSlider::GetValuePosition()
{
	return valuePos;
}

bool AdvSlider::GetValueEditable()
{
	return valueEditable;
}

void AdvSlider::SetValueEditable(bool val)
{
	if (val == valueEditable)
		return;
	if(valueObj!=NULL)
		lv_obj_del(valueObj);
	createValue();
}

void AdvSlider::setValue()
{
	if (valueEditable)
	{
		std::stringstream ss;
		switch (sliderType)
		{
		case AdvSlider::LONG_SLIDER:
			ss << lVal;
			break;
		case AdvSlider::FLOAT_SLIDER:
			ss << fVal;
			break;
		}
		lv_label_set_text(valueObj, ss.str().c_str());
		return;
	}
	
	// Its an editable object, set the text input value to the slider
}

void AdvSlider::createValue()
{
	if (!valueEditable)
	{
		valueObj = lv_label_create(container);
		setValue();
		return;
	}
	
	// Its an editable object, create a text input and assign a keyboard to it
	
}

void AdvSlider::draw(lv_obj_t *parent)
{
	container = lv_obj_create(parent);
	uint width = size.x2 - size.x1;
	uint height = size.y2 - size.y1;
	lv_obj_set_size(container, width, height);
	lv_obj_set_pos(container, size.x1, size.x2);
	sliderObj = lv_slider_create(container);

}

void AdvSlider::recomputeSlider()
{
}