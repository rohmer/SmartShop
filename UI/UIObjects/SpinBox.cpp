#include "SpinBox.h"

SpinBox::SpinBox(lv_obj_t *parent,
				 int x,
				 int y,
				 int width,
				 int maxValue,
				 int minValue,
				 int value,
				 int stepValue,
				 bool rollOver,
				 unsigned int integerPlaces,
				 unsigned int decimalPlaces,
				 ESpinBoxLabelPOS labelPos,
				 std::string label) :
	decimalPlaces(decimalPlaces)
{
	if (parent == nullptr)
		return;
	spinBox = lv_spinbox_create(parent);
	lv_spinbox_set_range(spinBox, minValue, maxValue);
	lv_spinbox_set_digit_format(spinBox, integerPlaces + decimalPlaces, integerPlaces);
	lv_spinbox_set_cursor_pos(spinBox, 0);
	if (stepValue != 1 || (stepValue % 10) != 0)
	{
		if (stepValue < 10)
			stepValue = 1;
		else
		{
			std::stringstream ss,s2;
			ss << stepValue;
			s2 << "1";
			for (int i = 0; i < ss.str().length() - 1; i++)
				s2 << "0";
			stepValue = std::atoi(s2.str().c_str());
		}
	}
	lv_spinbox_set_step(spinBox, stepValue);
	lv_obj_set_pos(spinBox, x, y);
	lv_obj_set_width(spinBox, width);

	incButton = lv_btn_create(parent);
	decButton = lv_btn_create(parent);
	lv_coord_t h = lv_obj_get_content_height(spinBox);
	lv_obj_set_size(incButton, h, h);
	lv_obj_set_size(decButton, h, h);
	lv_obj_align_to(incButton, spinBox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
	lv_obj_align_to(decButton, spinBox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
	lv_obj_set_style_bg_img_src(incButton, LV_SYMBOL_PLUS, 0);
	lv_obj_set_style_bg_img_src(decButton, LV_SYMBOL_MINUS, 0);
	lv_obj_add_event_cb(incButton, spinBoxIncrement, LV_EVENT_ALL, incButton);
	lv_obj_add_event_cb(decButton, spinBoxDecrement, LV_EVENT_ALL, decButton);

	if (label.size() > 0)
	{
		this->label = lv_label_create(parent);
		lv_label_set_text(this->label, label.c_str());
		if (ESpinBoxLabelPOS::E_LEFT)
			lv_obj_align_to(this->label, incButton, LV_ALIGN_OUT_LEFT_MID, -5, 0);
		else
			lv_obj_align_to(this->label, this->spinBox, LV_ALIGN_OUT_TOP_MID, 0, -5);
	}
}

void SpinBox::spinBoxDecrement(lv_event_t *event)
{
	lv_obj_t *spinbox=(lv_obj_t*)lv_event_get_user_data(event);
	lv_event_code_t code = lv_event_get_code(event);
	if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		lv_spinbox_decrement(spinbox);
	}
}

void SpinBox::spinBoxIncrement(lv_event_t *event)
{
	lv_obj_t *spinbox = (lv_obj_t*)lv_event_get_user_data(event);
	lv_event_code_t code = lv_event_get_code(event);
	if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
	{
		lv_spinbox_increment(spinbox);
	}
}

int SpinBox::GetIntValue()
{
	return (int)std::round(GetFloatValue());
}

float SpinBox::GetFloatValue()
{
	uint32_t v = lv_spinbox_get_value(spinBox);
	float divisor = 10 ^ decimalPlaces;
	return ((float)v / divisor);
}