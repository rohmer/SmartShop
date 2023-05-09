#include "InputField.h"

InputField::InputField(lv_obj_t *parent, std::string label, eInputType inputType, std::string value, uint x, uint y, uint width, uint height, int maxSize, eKBPreferredLocation prefferedLoc)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize),
	  prefLoc(prefferedLoc)
{
	createObjects(value, label);
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
	float maxValue,
	eKBPreferredLocation preferredLoc)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize),
	  fMaxValue(maxValue),
	  fMinValue(minValue),
	  prefLoc(preferredLoc)
{
	std::stringstream vs;
	vs << value;
	createObjects(vs.str(), label);
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
	int maxValue,
	eKBPreferredLocation preferredLoc)
	: parent(parent),
	  inputType(inputType),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  maxSize(maxSize),
	  iMaxValue(maxValue),
	  iMinValue(minValue),
	  prefLoc(preferredLoc)
{
	std::stringstream vs;
	vs << value;
	createObjects(vs.str(), label);
}

InputField::InputField(
	lv_obj_t *parent,
	std::string label,
	eInputType inputType,
	long value,
	uint x,
	uint y,
	uint width,
	uint height,
	int maxSize,
	long minValue,
	long maxValue,
	eKBPreferredLocation prefKBLoc) : parent(parent),
									  inputType(inputType),
									  x(x),
									  y(y),
									  width(width),
									  height(height),
									  maxSize(maxSize),
									  iMaxValue(maxValue),
									  iMinValue(minValue),
									  prefLoc(prefKBLoc)
{
	std::stringstream vs;
	vs << value;
	createObjects(vs.str(), label);
}

void InputField::createObjects(std::string value, std::string label)
{
	textArea = lv_textarea_create(parent);

	// If we have a layout this is moot
	lv_obj_set_pos(textArea, x, y);
	if (height < lv_font_default()->line_height + 5)
		height = lv_font_default()->line_height + 5;
	lv_obj_set_size(textArea, width, height);
	lv_textarea_set_max_length(textArea, maxSize);
	lv_textarea_set_text(textArea, value.c_str());
	if(label.size()>0)
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
	InputField *inputField = (InputField *)lv_event_get_user_data(e);
	if (inputField->GetInputType() == InputField::E_STRING || inputField->GetInputType() == InputField::E_MULTI_STRING)
		return;
	if (inputField->GetInputType() == InputField::E_INTEGER)
	{
		int v = inputField->GetIntValue();
		if (v > inputField->GetMaxI())
		{
			if (inputField->errMsg == NULL)
				inputField->errMsg = lv_label_create(lv_scr_act());
			lv_label_set_recolor(inputField->errMsg, true);
			std::stringstream ss;
			ss << "#FF0000 Greater than max value (" << inputField->GetMaxI() << ")#";
			lv_label_set_text(inputField->errMsg, ss.str().c_str());
			lv_obj_align_to(inputField->errMsg, inputField->taLabel, LV_ALIGN_RIGHT_MID, 0, 0);
			return;
		}
		else if (v < inputField->GetMinI())
		{
			if (inputField->errMsg == NULL)
				inputField->errMsg = lv_label_create(lv_scr_act());
			lv_label_set_recolor(inputField->errMsg, true);
			std::stringstream ss;
			ss << "#FF0000 Less than min value (" << inputField->GetMaxI() << ")#";
			lv_label_set_text(inputField->errMsg, ss.str().c_str());
			lv_obj_align_to(inputField->errMsg, inputField->taLabel, LV_ALIGN_RIGHT_MID, 0, 0);
			return;
		}
	}
	else
	{
		float v = inputField->GetFloatValue();
		if (v > inputField->GetMaxF())
		{
			if (inputField->errMsg == NULL)
				inputField->errMsg = lv_label_create(lv_scr_act());
			lv_label_set_recolor(inputField->errMsg, true);
			std::stringstream ss;
			ss << "#FF0000 Greater than max value (" << inputField->GetMaxF() << ")#";
			lv_label_set_text(inputField->errMsg, ss.str().c_str());
			lv_obj_align_to(inputField->errMsg, inputField->taLabel, LV_ALIGN_RIGHT_MID, 0, 0);
			return;
		}
		else
		{
			if (v < inputField->GetMinF())
			{
				if (inputField->errMsg == NULL)
					inputField->errMsg = lv_label_create(lv_scr_act());
				lv_label_set_recolor(inputField->errMsg, true);
				std::stringstream ss;
				ss << "#FF0000 Less than min value (" << inputField->GetMaxF() << ")#";
				lv_label_set_text(inputField->errMsg, ss.str().c_str());
				lv_obj_align_to(inputField->errMsg, inputField->taLabel, LV_ALIGN_RIGHT_MID, 0, 0);
				return;
			}
		}
	}
	if (inputField->errMsg != NULL)
		lv_obj_del(inputField->errMsg);
}

void InputField::keyboard_btn_handler(lv_event_t *e)
{
	lv_obj_t *obj = lv_event_get_target(e);
	InputField* inputField = (InputField*)lv_event_get_user_data(e);
	const char *txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

	if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0)
		lv_textarea_del_char(inputField->textArea);
	else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0 && inputField->GetInputType() != InputField::E_MULTI_STRING)
	{
		lv_keyboard_set_textarea(inputField->GetKeyboard(), NULL);
		lv_obj_add_flag(inputField->GetKeyboard(), LV_OBJ_FLAG_HIDDEN);
	}
	else if (strcmp(txt, LV_SYMBOL_OK) == 0 || strcmp(txt, LV_SYMBOL_KEYBOARD) == 0)
	{
		lv_keyboard_set_textarea(inputField->GetKeyboard(), NULL);
		lv_obj_add_flag(inputField->GetKeyboard(), LV_OBJ_FLAG_HIDDEN);
		;
	}
	else if (strcmp(txt, "+/-") == 0)
	{
		if (inputField->GetInputType() == InputField::E_INTEGER)
		{
			long i = inputField->GetIntValue()*-1;
			std::stringstream ss;
			ss << i;
			lv_textarea_set_text(inputField->textArea, ss.str().c_str());
		}
		if (inputField->GetInputType() == InputField::E_FLOAT)
		{
			double i = inputField->GetFloatValue() * -1;
			std::stringstream ss;
			ss << i;
			lv_textarea_set_text(inputField->textArea, ss.str().c_str());
		}
	}

	//else lv_textarea_add_text(inputField->textArea, txt);	
}

void InputField::createKeyboard()
{
	if (prefLoc == eKBPreferredLocation::NONE)
		prefLoc = eKBPreferredLocation::KB_TOP;
	switch (inputType)
	{
	case InputField::E_INTEGER:
	{
		keyboard = lv_keyboard_create(lv_scr_act());
		lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
		lv_obj_set_size(keyboard, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 2, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 2);
		static const char *int_map[] = {"1",
										"2",
										"3",
										"\n",
										"4",
										"5",
										"6",
										"\n",
										"7",
										"8",
										"9",
										"\n",
										LV_SYMBOL_LEFT,
										"0",
										LV_SYMBOL_RIGHT,
										"\n",
										LV_SYMBOL_OK,
										"+/-",
										LV_SYMBOL_BACKSPACE,
										""};

		static const lv_btnmatrix_ctrl_t int_ctrl_map[] = {
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			1,
			LV_KEYBOARD_CTRL_BTN_FLAGS | 1,
			1,
			LV_KEYBOARD_CTRL_BTN_FLAGS | 1,
			LV_KEYBOARD_CTRL_BTN_FLAGS | 1,
			1,
			LV_KEYBOARD_CTRL_BTN_FLAGS | 1
		};
		lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_NUMBER, int_map, int_ctrl_map);
		//lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

		lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
		setKBLocation();
		lv_keyboard_set_textarea(keyboard, textArea);
		break;
	}

	case InputField::E_FLOAT:
	{
		keyboard = lv_keyboard_create(lv_scr_act());
		lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
		lv_obj_set_size(keyboard, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 2, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 2);
		lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

		lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
		setKBLocation();
		lv_keyboard_set_textarea(keyboard, textArea);
		break;
	}
	default:
	{

		keyboard = lv_keyboard_create(lv_scr_act());
		lv_obj_set_size(keyboard, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 2, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 2);
		setKBLocation();
		lv_keyboard_set_textarea(keyboard, textArea);

		lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
		lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);
	}
	}
}

void InputField::setKBLocation()
{
	eKBPreferredLocation locations[5][4] = {
		{KB_LEFT, KB_RIGHT, KB_BOTTOM, KB_TOP},
		{KB_RIGHT, KB_LEFT, KB_BOTTOM, KB_TOP},
		{KB_TOP, KB_BOTTOM, KB_RIGHT, KB_LEFT},
		{KB_BOTTOM, KB_TOP, KB_RIGHT, KB_LEFT},
		{KB_BOTTOM, KB_RIGHT, KB_TOP, KB_LEFT}};

	lv_area_t taArea, kbArea;
	kbArea.x1 = 0;
	kbArea.x2 = lv_scr_act()->coords.x2 / 2;
	kbArea.y1 = 0;
	kbArea.y2 = lv_scr_act()->coords.y2 / 2;

	taArea.x1 = lv_obj_get_x(textArea) - 3;
	taArea.x2 = taArea.x1 + lv_obj_get_width(textArea) + 6;
	taArea.y1 = lv_obj_get_y(textArea) - 3;
	taArea.y2 = lv_obj_get_height(textArea) + 3;

	uint16_t kbMidV = (taArea.y2 - taArea.y1) / 2+taArea.y1;
	uint16_t kbMidH = (taArea.x2 - taArea.x1) / 2+taArea.x1;
	for (int i = 0; i < 4; i++)
	{
		switch (locations[prefLoc][i])
		{
		case KB_LEFT:
		{
			uint16_t x1 = taArea.x1 - (kbArea.x2 - kbArea.x1);
			uint16_t y1 = kbMidV + ((kbArea.y2 - kbArea.y1) / 2);
			lv_point_t np;
			np.x = x1;
			np.y = y1;
			if (Area::OnScreen(kbArea, np))
			{
				lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, -3, 0);
				return;
			}
			// We have the Y points off, lets move them and go on
			if (np.y < 0)
			{
				uint mod = abs(np.y);
				np.y = 1;
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, -3, mod);
					return;
				}
			}
			if (np.y > lv_scr_act()->coords.y2)
			{
				int mod = (np.y + (kbArea.y2 - kbArea.y1) - 3 - lv_scr_act()->coords.y2);
				np.y = lv_scr_act()->coords.y2 - 3 - (kbArea.y2 - kbArea.y1);
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, -3, mod);
					return;
				}
			}
			break;
		}
		case KB_RIGHT:
		{
			uint16_t x1 = taArea.x2;
			uint16_t y1 = kbMidV + ((kbArea.y2 - kbArea.y1) / 2);
			lv_point_t np;
			np.x = x1;
			np.y = y1;
			if (Area::OnScreen(kbArea, np))
			{
				lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
				return;
			}
			break;
			// If we have a case where the Y points are off, lets just move them and go on
			if (np.y < 0)
			{
				uint mod = abs(np.y);
				np.y = 1;
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 3, mod);
					return;
				}
			}
			if (np.y > lv_scr_act()->coords.y2)
			{
				int mod = (np.y + (kbArea.y2 - kbArea.y1) - 3- lv_scr_act()->coords.y2);
				np.y = lv_scr_act()->coords.y2 - 3 - (kbArea.y2 - kbArea.y1);
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 3, mod);
					return;
				}
			}
		}
		case KB_TOP:
		{
			uint16_t x1 = kbMidH - ((kbArea.x2 - kbArea.x1) / 2);
			uint16_t y1 = taArea.y1 - (kbArea.y2-kbArea.y1);
			lv_point_t np;
			np.x = x1;
			np.y = y1;
			if (Area::OnScreen(kbArea, np))
			{
				lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, 0, -3);
				return;
			}
			// If we have a case where the X points are off, lets just move them and go on
			if (np.x < 0)
			{
				uint mod = abs(np.x);
				np.x = 1;
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, mod, -3);
					return;
				}
			}
			int mod = (np.x + (kbArea.x2 - kbArea.x1) - lv_scr_act()->coords.x2);
			np.x = lv_scr_act()->coords.x2 - 3 - (kbArea.x2 - kbArea.x1);
			if (Area::OnScreen(kbArea, np))
			{
				lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_LEFT, mod, -3);
				return;
			}
			break;
		}
		case KB_BOTTOM:
		{
			uint16_t x1 = kbMidH - ((kbArea.x2 - kbArea.x1) / 2);
			uint16_t y1 = taArea.y1;
			lv_point_t np;
			np.x = x1;
			np.y = y1;
			if (Area::OnScreen(kbArea, np))
			{
				lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);
				return;
			}
			// If we have a case where the X points are off, lets just move them and go on
			if (np.x < 0)
			{
				uint mod = abs(np.x);
				np.x = 1;
				if (Area::OnScreen(kbArea, np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, mod, 3);
					return;
				}
			}
			if (np.x + (kbArea.x2 - kbArea.x1) > lv_scr_act()->coords.x2)
			{
				int mod = (np.x + (kbArea.x2 - kbArea.x1) - lv_scr_act()->coords.x2);
				np.x = lv_scr_act()->coords.x2 - 3 - (kbArea.x2 - kbArea.x1);
				if (Area::OnScreen(kbArea,np))
				{
					lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, mod, 3);
					return;
				}
			}
			break;
		}
		}
	}
	// This should never happen, but we fell thru without a match, lets make the keyboard 10% smaller and try again
	lv_obj_set_size(keyboard, (lv_obj_get_width(keyboard)*0.9), lv_obj_get_height(keyboard)*0.9);
	setKBLocation();
}

void InputField::textArea_clicked(lv_event_t *e)
{
	InputField *inputField = (InputField *)lv_event_get_user_data(e);

	if (e->code == LV_EVENT_READY)
	{
		// Enter will close the keyboard on any non-multistring
		if (inputField->GetInputType() != InputField::E_MULTI_STRING)
		{
			lv_keyboard_set_textarea(inputField->GetKeyboard(), NULL);
			lv_obj_add_flag(inputField->GetKeyboard(), LV_OBJ_FLAG_HIDDEN);
		}
	}
	if (e->code == LV_EVENT_DEFOCUSED)
	{
		if (inputField->GetKeyboard() != NULL)
		{
			lv_keyboard_set_textarea(inputField->GetKeyboard(), NULL);
			lv_obj_add_flag(inputField->GetKeyboard(), LV_OBJ_FLAG_HIDDEN);
			return;
		}
	}
	if (e->code != LV_EVENT_CLICKED)
		return;

	if (inputField->keyboard == NULL)
	{
		inputField->createKeyboard();
	}
	if (inputField->GetKeyboard() != NULL)
		lv_obj_clear_flag(inputField->GetKeyboard(), LV_OBJ_FLAG_HIDDEN);
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

lv_area_t InputField::GetArea()
{
	lv_area_t ret;
	ret.x1 = std::min(lv_obj_get_x(taLabel), lv_obj_get_x(textArea));
	ret.y1 = std::min(lv_obj_get_y(taLabel), lv_obj_get_y(textArea));
	lv_area_t tArea;
	lv_obj_get_coords(textArea,&tArea);
	lv_area_t lArea;
	lv_obj_get_coords(taLabel, &lArea);
	ret.x2 = std::max(tArea.x2, lArea.x2);
	ret.y2 = std::max(tArea.y2, lArea.y2);
	return ret;
}