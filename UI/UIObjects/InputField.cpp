#include "InputField.h"

InputField::InputField(lv_obj_t *parent, std::string label, eInputType inputType, std::string value, uint x, uint y, uint width, uint height, int maxSize)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize)
{
	textArea = lv_textarea_create(parent);
	
	// If we have a layout this is moot
	lv_obj_set_pos(textArea, x, y);
	lv_obj_set_size(textArea, width, height);
	lv_textarea_set_max_length(textArea, maxSize);
	lv_textarea_set_text(textArea, value.c_str());
	lv_obj_t *taLabel = lv_label_create(parent);
	lv_label_set_text(taLabel, label.c_str());
	lv_obj_align_to(taLabel, textArea, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
	switch (inputType)
	{
	case InputField::E_INTEGER:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789");
		break;
	}
	case InputField::E_FLOAT:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789.");
		break;
	}
	case InputField::E_STRING:
	{
		lv_textarea_set_one_line(textArea, true);		
		break;
	}
	case InputField::E_MULTI_STRING:
	{
		lv_textarea_set_one_line(textArea, false);
	}
	}

		
	lv_obj_add_event_cb(textArea, textArea_clicked, LV_EVENT_CLICKED, this);
	lv_obj_add_event_cb(textArea, textArea_valueChanged, LV_EVENT_VALUE_CHANGED, this);
}

InputField::InputField(
	lv_obj_t *parent,
	std::string label,
	eInputType inputType,
	float value,
	uint x,
	uint y,
	uint width,
	uint height,
	int maxSize,
	float minValue,
	float maxValue)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize),
	  fMaxValue(maxValue),
	  fMinValue(minValue)
{
	textArea = lv_textarea_create(parent);

	// If we have a layout this is moot
	lv_obj_set_pos(textArea, x, y);
	lv_obj_set_size(textArea, width, height);
	lv_textarea_set_max_length(textArea, maxSize);
	std::stringstream ss;
	ss << value;
	lv_textarea_set_text(textArea, ss.str().c_str());
	lv_obj_t *taLabel = lv_label_create(parent);
	lv_label_set_text(taLabel, label.c_str());
	lv_obj_align_to(taLabel, textArea, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
	switch (inputType)
	{
	case InputField::E_INTEGER:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789");
		break;
	}
	case InputField::E_FLOAT:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789.");
		break;
	}
	case InputField::E_STRING:
	{
		lv_textarea_set_one_line(textArea, true);
		break;
	}
	case InputField::E_MULTI_STRING:
	{
		lv_textarea_set_one_line(textArea, false);
	}
	}

	lv_obj_add_event_cb(textArea, textArea_clicked, LV_EVENT_CLICKED, this);
	lv_obj_add_event_cb(textArea, textArea_valueChanged, LV_EVENT_VALUE_CHANGED, this);
}

InputField::InputField(
	lv_obj_t *parent,
	std::string label,
	eInputType inputType,
	int value,
	uint x,
	uint y,
	uint width,
	uint height,
	int maxSize,
	int minValue,
	int maxValue)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize),
	  iMaxValue(maxValue),
	  iMinValue(minValue)
{
	textArea = lv_textarea_create(parent);

	// If we have a layout this is moot
	lv_obj_set_pos(textArea, x, y);
	lv_obj_set_size(textArea, width, height);
	lv_textarea_set_max_length(textArea, maxSize);
	std::stringstream ss;
	ss << value;
	lv_textarea_set_text(textArea, ss.str().c_str());
	lv_obj_t *taLabel = lv_label_create(parent);
	lv_label_set_text(taLabel, label.c_str());
	lv_obj_align_to(taLabel, textArea, LV_ALIGN_OUT_TOP_LEFT, 0, 0);
	switch (inputType)
	{
	case InputField::E_INTEGER:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789");
		break;
	}
	case InputField::E_FLOAT:
	{
		lv_textarea_set_one_line(textArea, true);
		lv_textarea_set_accepted_chars(textArea, "-+0123456789.");
		break;
	}
	case InputField::E_STRING:
	{
		lv_textarea_set_one_line(textArea, true);
		break;
	}
	case InputField::E_MULTI_STRING:
	{
		lv_textarea_set_one_line(textArea, false);
	}
	}

	lv_obj_add_event_cb(textArea, textArea_clicked, LV_EVENT_CLICKED, this);
	lv_obj_add_event_cb(textArea, textArea_valueChanged, LV_EVENT_VALUE_CHANGED, this);
}

void InputField::textArea_valueChanged(lv_event_t *e)
{
	InputField *inputField = (InputField*)lv_event_get_user_data(e);
	if (inputField->GetInputType() == InputField::E_STRING || inputField->GetInputType() == InputField::E_MULTI_STRING)
		return;
	if (inputField->GetInputType() == InputField::E_INTEGER)
	{
		int v = inputField->GetIntValue();
		if (v > inputField->GetMaxI())
		{
			std::stringstream ss;
			ss << inputField->GetMaxI();
			lv_textarea_set_text(inputField->GetTextArea(), ss.str().c_str());
		}
		else
		{
			if (v < inputField->GetMinI())
			{
				std::stringstream ss;
				ss << inputField->GetMinI();
				lv_textarea_set_text(inputField->GetTextArea(), ss.str().c_str());
			}
		}
	}
	else
	{
		float v = inputField->GetFloatValue();
		if (v > inputField->GetMaxF())
		{
			std::stringstream ss;
			ss << inputField->GetMaxF();
			lv_textarea_set_text(inputField->GetTextArea(), ss.str().c_str());
		}
		else
		{
			if (v < inputField->GetMinF())
			{
				std::stringstream ss;
				ss << inputField->GetMinF();
				lv_textarea_set_text(inputField->GetTextArea(), ss.str().c_str());
			}
		}
	}
}

void InputField::keyboard_btn_handler(lv_event_t *e)
{
	lv_obj_t *obj = lv_event_get_target(e);
	lv_obj_t *ta = (lv_obj_t*)lv_event_get_user_data(e);
	const char *txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

	if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0)
		lv_textarea_del_char(ta);
	else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0)
		lv_event_send(ta, LV_EVENT_READY, NULL);
	else
		lv_textarea_add_text(ta, txt);	
}

void InputField::textArea_clicked(lv_event_t *e)
{
	InputField *inputField = (InputField *)lv_event_get_user_data(e);
	if (inputField->GetKeyboard() != NULL)
	{
		lv_obj_del_async(inputField->GetKeyboard());
		return;
	}

	inputField->SetKeyboard(lv_keyboard_create(lv_scr_act()));

	switch (inputField->GetInputType())
	{
	case InputField::E_INTEGER:
	{
		static const char *btnm_map[] = {"1", "2", "3", "\n",
										 "4", "5", "6", "\n",
										 "7", "8", "9", "\n",
										 LV_SYMBOL_BACKSPACE, "0", "", ""};

		lv_obj_t *btnm = lv_btnmatrix_create(lv_scr_act());
		lv_obj_set_size(btnm, 200, 150);
		lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -10);
		lv_obj_add_event_cb(btnm, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, inputField->GetTextArea());
		lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
		lv_btnmatrix_set_map(btnm, btnm_map);
		inputField->SetKeyboard(btnm);
		int pos = lv_obj_get_y(inputField->GetTextArea()) + lv_obj_get_height(inputField->GetTextArea()) + 5;
		if (pos + 150 > lv_scr_act()->coords.y2)
		{
			lv_obj_align_to(inputField->GetKeyboard(), inputField->GetTextArea(), LV_ALIGN_OUT_TOP_MID, 0, 0);
		}
		else
		{
			lv_obj_align_to(inputField->GetKeyboard(), inputField->GetTextArea(), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		}
		break;
	}

	case InputField::E_FLOAT:
	{
		lv_obj_t *kb=lv_keyboard_create(lv_scr_act());
		lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
		lv_obj_set_size(kb, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 3, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 3);
		int pos = lv_obj_get_y(inputField->GetTextArea()) + lv_obj_get_height(inputField->GetTextArea()) + 5;		
		if (pos + lv_obj_get_height(inputField->GetTextArea()) > lv_scr_act()->coords.y2)
		{
			lv_obj_align_to(kb, inputField->GetTextArea(), LV_ALIGN_OUT_TOP_MID, 0, 0);
		}
		else
		{
			lv_obj_align_to(kb, inputField->GetTextArea(), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		}
		lv_keyboard_set_textarea(kb, inputField->GetTextArea());
		inputField->SetKeyboard(kb);
		break;
	}
	default:
	{
		lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
		lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);
		lv_obj_set_size(kb, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 3, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 3);
		int pos = lv_obj_get_y(inputField->GetTextArea()) + lv_obj_get_height(inputField->GetTextArea()) + 5;
		if (pos + lv_obj_get_height(inputField->GetTextArea()) > lv_scr_act()->coords.y2)
		{
			lv_obj_align_to(kb, inputField->GetTextArea(), LV_ALIGN_OUT_TOP_MID, 0, 0);
		}
		else
		{
			lv_obj_align_to(kb, inputField->GetTextArea(), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		}
		lv_keyboard_set_textarea(kb, inputField->GetTextArea());
		inputField->SetKeyboard(kb);
	}
	}
}

std::string InputField::GetStringValue()
{
	std::string v(lv_textarea_get_text(textArea));
	return v;
}

int InputField::GetIntValue()
{
	if (inputType != InputField::E_INTEGER)
		return 0;
	int i = std::atoi(lv_textarea_get_text(textArea));
	return i;
}

float InputField::GetFloatValue()
{
	if (inputType != InputField::E_FLOAT)
		return 0;
	float f= std::atof(lv_textarea_get_text(textArea));
	return f;
}