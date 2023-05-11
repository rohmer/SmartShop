#pragma once

#include <limits>
#include <lvgl.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Area.h"

template <typename T>
class InputField
{
  public:
	enum eInputFieldValueType
	{
		INTEGRAL_INPUT_VALUE_TYPE,
		FLOATING_POINT_INPUT_VALUE_TYPE,
		UNSIGNED_INTEGRAL_INPUT_VALUE_TYPE,
		UNSIGNED_FLOATING_POINT_INPUT_VALUE_TYPE,
		STRING_VALUE_TYPE,
		UNKNOWN_VALUE_TYPE
	};

	enum eKBPreferredLocation
	{
		KB_LEFT = 0,
		KB_RIGHT = 1,
		KB_TOP = 2,
		KB_BOTTOM = 3,
		KB_NONE = 4
	};

	InputField(lv_obj_t *parent,
				T value,
				lv_coord_t x,
				lv_coord_t y,
				lv_coord_t width,
				lv_coord_t height) : parent(parent),
									 x(x),
									 y(y),
									 width(width),
									 height(height),
									 value(value),
									 kbPrefLoc(KB_BOTTOM)
	{
		createObjects();
	}

	~InputField()
	{
		if (textArea != NULL)
			lv_obj_del_async(textArea);
		if (labelObj != NULL)
			lv_obj_del_async(labelObj);
		if (errMsg != NULL)
			lv_obj_del_async(errMsg);
	}

	void SetValue(T value)
	{
		if (valueType != STRING_VALUE_TYPE || valueType != UNKNOWN_VALUE_TYPE)
		{
			if (value > maxValue)
				value = maxValue;
			if (value < minValue)
				value = minValue;
		}
		this->value = value;
		std::stringstream ss;
		ss << value;
		lv_textarea_set_text(textArea, ss.str().c_str());		
	}
	
	lv_obj_t *GetObject()
	{
		return textArea;
	}

	void SetWidth(lv_coord_t width)
	{
		if (labelObj == NULL)
			return;
		lv_obj_set_width(labelObj, width);
	}

	lv_coord_t GetWidth()
	{
		if (labelObj == NULL)
			return 0;
		return lv_obj_get_width(labelObj);
	}

	void SetHeight(lv_coord_t height)
	{
		if (labelObj == NULL)
			return;
		lv_obj_set_height(labelObj, height);
	}

	lv_coord_t GetHeight()
	{
		if (labelObj == NULL)
			return 0;
		return lv_obj_get_height(labelObj);
	}
	
	void SetLabel(std::string label, lv_align_t alignment=LV_ALIGN_OUT_RIGHT_MID, uint xOff=0, uint yOff=0)
	{
		if (labelObj == NULL)
			labelObj = lv_label_create(parent);
		lv_label_set_text(labelObj, label.c_str());
		if (textArea != NULL)
			lv_obj_align_to(labelObj, textArea, alignment, xOff, yOff);
	}

	void SetMaxLength(uint maxLength)
	{
		lv_textarea_set_max_length(textArea, maxLength);
	}

	void SetStringMultiline(bool value)
	{
		if (valueType != InputField::STRING_VALUE_TYPE)
		{
			lv_textarea_set_one_line(textArea, true);
		}
		lv_textarea_set_one_line(textArea, !value);
	}

	void SetKBPreferredLocation(eKBPreferredLocation loc)
	{
		kbPrefLoc = loc;
	}

	eKBPreferredLocation GetKBPreferredLocation()
	{
		return kbPrefLoc;
	}

	eInputFieldValueType GetInputFieldType()
	{
		return valueType;
	}

	void SetMaxValue(T max)
	{
		maxValue = max;
	}
	
	void SetMinValue(T min)
	{
		minValue = min;
	}

	decltype(auto) GetMinValue()
	{
		return minValue;
	}

	decltype(auto) GetMaxValue()
	{
		return maxValue;
	}

	std::string GetStringValue()
	{
		if (textArea == NULL)
			return "";
		return lv_textarea_get_text(textArea);
	}

	double GetDoubleValue()
	{
		if (textArea == NULL)
			return 0;
		return std::atof(lv_textarea_get_text(textArea));
	}

	long GetLongValue()
	{
		if (textArea == NULL)
			return 0;
		return std::atol(lv_textarea_get_text(textArea));
	}
	
	lv_area_t GetArea()
	{
		lv_area_t ret;
		if (labelObj != NULL)
		{
			ret.x1 = std::min(lv_obj_get_x(labelObj), lv_obj_get_x(textArea));
			ret.y1 = std::min(lv_obj_get_y(labelObj), lv_obj_get_y(textArea));
			lv_area_t tArea;
			lv_obj_get_coords(textArea, &tArea);
			lv_area_t lArea;
			lv_obj_get_coords(labelObj, &lArea);
			ret.x2 = std::max(tArea.x2, lArea.x2);
			ret.y2 = std::max(tArea.y2, lArea.y2);
			return ret;
		}
		lv_obj_get_coords(textArea, &ret);
		return ret;
	}


  private:
	lv_coord_t x, y, width, height;
	lv_obj_t *parent;

	T maxValue, minValue;
	T value;
	eInputFieldValueType valueType;
	eKBPreferredLocation kbPrefLoc;

	lv_obj_t *textArea = NULL, *labelObj = NULL, *keyboard = NULL, *errMsg = NULL;

	void createObjects()
	{
		textArea = lv_textarea_create(parent);

		// If we have a layout this is moot
		lv_obj_set_pos(textArea, x, y);
		if (height < lv_font_default()->line_height + 5)
			height = lv_font_default()->line_height + 5;
		lv_obj_set_size(textArea, width, height);
		std::stringstream ss;
		ss << value;		
		lv_textarea_set_text(textArea, ss.str().c_str());
		SetStringMultiline(false);
		if (std::is_arithmetic<T>::value)
		{
			if (std::is_floating_point<T>::value)
			{
				if (std::is_signed<T>::value)
					valueType = InputField::FLOATING_POINT_INPUT_VALUE_TYPE;
				else
					valueType = InputField::UNSIGNED_FLOATING_POINT_INPUT_VALUE_TYPE;
			}
			else
			{
				if (std::is_signed<T>::value)
					valueType = InputField::INTEGRAL_INPUT_VALUE_TYPE;
				else
					valueType = InputField::UNSIGNED_INTEGRAL_INPUT_VALUE_TYPE;
			}
		}
		else
		{
			if (std::is_same<T, std::string>::value ||
				std::is_same<T, char *>::value ||
				std::is_same<T, char[]>::value)
			{
				valueType = InputField::STRING_VALUE_TYPE;
			}
			else
			{
				valueType = InputField::UNKNOWN_VALUE_TYPE;
			}
		}
		switch (valueType)
		{
		case InputField::INTEGRAL_INPUT_VALUE_TYPE:
			lv_textarea_set_accepted_chars(textArea,"-+0123456789");
			break;
		case InputField::FLOATING_POINT_INPUT_VALUE_TYPE:
			lv_textarea_set_accepted_chars(textArea, "-+0123456789.");
			break;
		}
		

		lv_obj_add_event_cb(textArea, textArea_clicked, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(textArea, textArea_valueChanged, LV_EVENT_VALUE_CHANGED, this);
	}

	void createKeyboard()
	{
		if (kbPrefLoc == eKBPreferredLocation::KB_NONE)
			kbPrefLoc = eKBPreferredLocation::KB_TOP;
		switch (GetInputFieldType())
		{
		case InputField::INTEGRAL_INPUT_VALUE_TYPE:
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
				LV_KEYBOARD_CTRL_BTN_FLAGS | 1};
			lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_NUMBER, int_map, int_ctrl_map);
			
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
			setKBLocation();
			lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

			lv_keyboard_set_textarea(keyboard, textArea);
			break;
		}
		case InputField::UNSIGNED_INTEGRAL_INPUT_VALUE_TYPE:
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
				LV_KEYBOARD_CTRL_BTN_FLAGS | 2};
			lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_NUMBER, int_map, int_ctrl_map);

			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
			setKBLocation();
			lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

			lv_keyboard_set_textarea(keyboard, textArea);
			break;
		}
		case InputField::FLOATING_POINT_INPUT_VALUE_TYPE:
		{
			keyboard = lv_keyboard_create(lv_scr_act());
			lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
			lv_obj_set_size(keyboard, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 2, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 2);
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
			setKBLocation();
			lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

			lv_keyboard_set_textarea(keyboard, textArea);
			break;
		}
		case InputField::UNSIGNED_FLOATING_POINT_INPUT_VALUE_TYPE:
		{
			keyboard = lv_keyboard_create(lv_scr_act());
			lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_NUMBER);
			static const char *ufp_kb_map[] = {"1", "2", "3", LV_SYMBOL_KEYBOARD, "\n",
															 "4", "5", "6", LV_SYMBOL_OK, "\n",
															 "7", "8", "9", LV_SYMBOL_BACKSPACE, "\n",
															  "0", ".", LV_SYMBOL_LEFT, LV_SYMBOL_RIGHT, ""};

			static const lv_btnmatrix_ctrl_t ufp_kb_ctrl_map[] = {
				1, 1, 1, LV_KEYBOARD_CTRL_BTN_FLAGS | 2,
				1, 1, 1, LV_KEYBOARD_CTRL_BTN_FLAGS | 2,
				1, 1, 1, 2,
				2, 1, 1, 1};
			lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_NUMBER, ufp_kb_map, ufp_kb_ctrl_map);
			lv_obj_set_size(keyboard, (lv_scr_act()->coords.x2 - lv_scr_act()->coords.x1) / 2, (lv_scr_act()->coords.y2 - lv_scr_act()->coords.y1) / 2);
			lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
			setKBLocation();
			lv_obj_add_event_cb(keyboard, keyboard_btn_handler, LV_EVENT_VALUE_CHANGED, (void *)this);

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
	
	void setKBLocation()
	{
		if (keyboard == NULL)
			createKeyboard();
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

		uint16_t kbMidV = (taArea.y2 - taArea.y1) / 2 + taArea.y1;
		uint16_t kbMidH = (taArea.x2 - taArea.x1) / 2 + taArea.x1;
		for (int i = 0; i < 4; i++)
		{
			switch (locations[kbPrefLoc][i])
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
					int mod = (np.y + (kbArea.y2 - kbArea.y1) - 3 - lv_scr_act()->coords.y2);
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
				uint16_t y1 = taArea.y1 - (kbArea.y2 - kbArea.y1);
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
					if (Area::OnScreen(kbArea, np))
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
		lv_obj_set_size(keyboard, (lv_obj_get_width(keyboard) * 0.9), lv_obj_get_height(keyboard) * 0.9);
		setKBLocation();
	}
	
	static void textArea_clicked(lv_event_t *e)
	{
		InputField *inputField = (InputField *)lv_event_get_user_data(e);
		if (e->code == LV_EVENT_READY)
		{
			// Enter will close the keyboard on any non-multistring
			if (lv_textarea_get_one_line(inputField->textArea))
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

	static void textArea_valueChanged(lv_event_t *e)
	{
		InputField *inputField = (InputField *)lv_event_get_user_data(e);

		if (inputField->GetInputFieldType() == InputField::STRING_VALUE_TYPE)
			return;
		// We are a numeric type
		std::stringstream msg;
		bool showErr = false;
		if (inputField->GetInputFieldType() == InputField::FLOATING_POINT_INPUT_VALUE_TYPE)
		{
			double max = ((InputField<double>*)inputField)->GetMaxValue();
			double min = ((InputField<double>*)inputField)->GetMinValue();
			if (max != 0 && min != 0)
			{
				if (inputField->GetDoubleValue() > max)
				{
					msg << "#FF0000 Greater than max value (" << max << ")#";
					showErr = true;
				}
				else
				{
					msg << "#FF0000 Less than min value (" << min << ")#";
					showErr = true;
				}
			}
		}
		if (inputField->GetInputFieldType() == InputField::INTEGRAL_INPUT_VALUE_TYPE)
		{
			long long max = ((InputField<long long> *)inputField)->GetMaxValue();
			long long min = ((InputField<long long> *)inputField)->GetMinValue();
			if (max != 0 && min != 0)
			{
				if (inputField->GetLongValue()> max)
				{
					msg << "#FF0000 Greater than max value (" << max << ")#";
					showErr = true;
				}
				else
				{
					msg << "#FF0000 Less than min value (" << min << ")#";
					showErr = true;
				}
			}
		}
		if (showErr)
		{
			if (inputField->errMsg == NULL)
				inputField->errMsg = lv_label_create(lv_scr_act());
			lv_label_set_recolor(inputField->errMsg, true);
			lv_label_set_text(inputField->errMsg, msg.str().c_str());
			lv_obj_align_to(inputField->errMsg, inputField->labelObj, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
			return;
		}
		if (inputField->errMsg != NULL)
			lv_obj_del(inputField->errMsg);
	}

	static void keyboard_btn_handler(lv_event_t *e)
	{
		lv_obj_t *obj = lv_event_get_target(e);
		InputField *inputField = (InputField *)lv_event_get_user_data(e);
		const char *txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

		if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0)
			lv_textarea_del_char(inputField->textArea);
		else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0 && lv_textarea_get_one_line(inputField->textArea))
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
			if (std::is_signed<T>::value)
			{
				if (std::is_floating_point<T>::value)
				{
					double i = ((InputField<double> *)inputField)->GetDoubleValue() * -1.0;
					std::stringstream ss;
					ss << i;
					lv_textarea_set_text(inputField->textArea, ss.str().c_str());
				}
				else
				{
					long i = ((InputField<long long> *)inputField)->GetLongValue() * -1;
					std::stringstream ss;
					ss << i;
					lv_textarea_set_text(inputField->textArea, ss.str().c_str());
				}
			}
		}
	}

	lv_obj_t *GetKeyboard()
	{
		return keyboard;
	}
};