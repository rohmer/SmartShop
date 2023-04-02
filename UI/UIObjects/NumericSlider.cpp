#include "NumericSlider.h"

NumericSlider::NumericSlider(
	lv_obj_t *parent,
	uint x,
	uint y,
	uint width,
	uint height,
	int value,
	int maxValue,
	int minValue,
	lv_align_t numbersAlign) : valueAlign(numbersAlign),
							   isDrawer(false)
{
	sliderObj = lv_slider_create(parent);
	lv_obj_set_pos(sliderObj, x, y);
	lv_obj_set_size(sliderObj, width, height);
	lv_slider_set_range(sliderObj, minValue, maxValue);
	

	valueObj = lv_label_create(parent);
	std::stringstream ss;
	ss << value;
	lv_label_set_text(valueObj, ss.str().c_str());
	lv_obj_align_to(valueObj, 
					parent, 
					numbersAlign, 
					Utils::GetDX(numbersAlign), 
					Utils::GetDY(numbersAlign)
					);
	if (value > maxValue)
		value = maxValue;
	if (value < minValue)
		value = minValue;
	lv_slider_set_value(sliderObj, value, LV_ANIM_OFF);
	lv_obj_add_event_cb(sliderObj, slider_event_cb, LV_EVENT_VALUE_CHANGED, this);
}

NumericSlider::NumericSlider(
	lv_obj_t *parent,
	uint x,
	uint y,
	uint width,
	uint height,
	std::string label,
	lv_align_t labelAlign,
	int value,
	int maxValue,
	int minValue,
	lv_align_t numbersAlign) : valueAlign(numbersAlign),
							   isDrawer(false)
{
	sliderObj = lv_slider_create(parent);
	lv_obj_set_pos(sliderObj, x, y);
	lv_obj_set_size(sliderObj, width, height);
	lv_slider_set_range(sliderObj, minValue, maxValue);

	valueObj = lv_label_create(parent);
	std::stringstream ss;
	ss << value;
	lv_label_set_text(valueObj, ss.str().c_str());
	lv_obj_align_to(valueObj,
					parent,
					numbersAlign,
					Utils::GetDX(numbersAlign),
					Utils::GetDY(numbersAlign));
	if (value > maxValue)
		value = maxValue;
	if (value < minValue)
		value = minValue;

	labelObj = lv_label_create(parent);
	lv_slider_set_value(sliderObj, value, LV_ANIM_OFF);
	lv_obj_align_to(labelObj,
					parent,
					labelAlign,
					Utils::GetDX(labelAlign),
					Utils::GetDY(labelAlign));

	lv_label_set_text(labelObj, label.c_str());
	lv_obj_add_event_cb(sliderObj, slider_event_cb, LV_EVENT_VALUE_CHANGED, this);
}

NumericSlider::NumericSlider(
	lv_obj_t *parent,
	uint x,
	uint y,
	uint width,
	uint height,
	int leftValue,
	int rightValue,
	int maxValue,
	int minValue,
	lv_align_t numbersAlign) : valueAlign(numbersAlign),
							   isDrawer(true)
{
	sliderObj = lv_slider_create(parent);
	lv_obj_set_pos(sliderObj, x, y);
	lv_obj_set_size(sliderObj, width, height);
	lv_slider_set_range(sliderObj, minValue, maxValue);
	lv_slider_set_mode(sliderObj, LV_SLIDER_MODE_RANGE);
	valueObj = lv_label_create(parent);
	std::stringstream ss;
	ss << lv_slider_get_left_value(sliderObj) << " - " << lv_slider_get_value(sliderObj);
	lv_obj_align_to(valueObj,
					parent,
					numbersAlign,
					Utils::GetDX(numbersAlign),
					Utils::GetDY(numbersAlign));
	if (leftValue > maxValue)
		leftValue = maxValue;
	if (leftValue < minValue)
		leftValue = minValue;
	if (rightValue > maxValue)
		rightValue = maxValue;
	if (rightValue < minValue)
		rightValue = minValue;
	lv_slider_set_left_value(sliderObj, leftValue,LV_ANIM_OFF);
	lv_slider_set_value(sliderObj, rightValue, LV_ANIM_OFF);
	lv_obj_add_event_cb(sliderObj, slider_drawer_event_cb, LV_EVENT_VALUE_CHANGED, this);
}

NumericSlider::NumericSlider(
	lv_obj_t *parent,
	uint x,
	uint y,
	uint width,
	uint height,
	std::string label,
	lv_align_t labelAlign,
	int leftValue,
	int rightValue,
	int maxValue,
	int minValue,
	lv_align_t numbersAlign) : valueAlign(numbersAlign),
							   isDrawer(true)
{
	sliderObj = lv_slider_create(parent);
	lv_obj_set_pos(sliderObj, x, y);
	lv_obj_set_size(sliderObj, width, height);
	lv_slider_set_range(sliderObj, minValue, maxValue);
	lv_slider_set_mode(sliderObj, LV_SLIDER_MODE_RANGE);
	valueObj = lv_label_create(parent);
	std::stringstream ss;
	ss << lv_slider_get_left_value(sliderObj) << " - " << lv_slider_get_value(sliderObj);
	lv_obj_align_to(valueObj,
					parent,
					numbersAlign,
					Utils::GetDX(numbersAlign),
					Utils::GetDY(numbersAlign));
	if (leftValue > maxValue)
		leftValue = maxValue;
	if (leftValue < minValue)
		leftValue = minValue;
	if (rightValue > maxValue)
		rightValue = maxValue;
	if (rightValue < minValue)
		rightValue = minValue;
	lv_slider_set_left_value(sliderObj, leftValue, LV_ANIM_OFF);
	lv_slider_set_value(sliderObj, rightValue, LV_ANIM_OFF);
	lv_obj_add_event_cb(sliderObj, slider_drawer_event_cb, LV_EVENT_VALUE_CHANGED, this);
	labelObj = lv_label_create(parent);
	lv_obj_align_to(labelObj,
					parent,
					labelAlign,
					Utils::GetDX(labelAlign),
					Utils::GetDY(labelAlign));

	lv_label_set_text(labelObj, label.c_str());
}

NumericSlider::~NumericSlider()
{
	if (sliderObj != NULL)
		lv_obj_del_async(sliderObj);
	if (labelObj != NULL)
		lv_obj_del_async(labelObj);
	if (valueObj != NULL)
		lv_obj_del_async(valueObj);
}

int NumericSlider::GetValue()
{
	return lv_slider_get_value(sliderObj);
}

int NumericSlider::GetRightValue()
{
	return GetValue();
}

int NumericSlider::GetLeftValue()
{
	if (isDrawer)
		return lv_slider_get_left_value(sliderObj);
	return GetValue();
}

int NumericSlider::GetMaxValue()
{
	return lv_slider_get_max_value(sliderObj);
}

int NumericSlider::GetMinValue()
{
	return lv_slider_get_min_value(sliderObj);
}

lv_align_t NumericSlider::GetValueAlign()
{
	return valueAlign;
}

lv_obj_t *NumericSlider::GetValueObject()
{
	return valueObj;
}

lv_obj_t *NumericSlider::GetSliderObject()
{
	return sliderObj;
}

void NumericSlider::slider_event_cb(lv_event_t *e)
{
	NumericSlider *ns = (NumericSlider *)lv_event_get_user_data(e);

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	/*Provide some extra space for the value*/
	if (code == LV_EVENT_REFR_EXT_DRAW_SIZE)
	{
		lv_event_set_ext_draw_size(e, 50);
	}
	
	std::stringstream ss;
	ss << lv_slider_get_value(lv_event_get_target(e));
	lv_label_set_text(ns->GetValueObject(), ss.str().c_str());
	lv_obj_align_to(
		ns->GetValueObject(),
		ns->GetSliderObject(),
		ns->GetValueAlign(),
		Utils::GetDX(ns->GetValueAlign()),
		Utils::GetDY(ns->GetValueAlign()));
}

void NumericSlider::slider_drawer_event_cb(lv_event_t *e)
{
	NumericSlider *ns = (NumericSlider *)lv_event_get_user_data(e);
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	/*Provide some extra space for the value*/
	if (code == LV_EVENT_REFR_EXT_DRAW_SIZE)
	{
		lv_event_set_ext_draw_size(e, 50);
	}

	char buf[16];
	lv_snprintf(buf, sizeof(buf), "%d - %d", (int)lv_slider_get_left_value(obj), (int)lv_slider_get_value(obj));
	lv_label_set_text(ns->GetValueObject(), buf);
}
