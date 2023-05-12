#pragma once

#include <string>
#include <lvgl.h>
#include "../../Logger/Logger.h"
#include "../../Device/DeviceConfigItem.h"
#include "AdvLine.h"
#include "AdvSlider.h"

class PropertyDrawer
{
  public:
	enum ePropType
	{
		STRING_PROP,
		ENUM_STRING_PROP,
		BOOL_PROP,
		INT_PROP,
		INT_BOUNDED_TYPE,
		FLOAT_TYPE,
		FLOAT_BOUNDED_TYPE
	}; 
	
	PropertyDrawer(DeviceConfigItem &deviceConfigItem, lv_obj_t *parent, lv_coord_t verticalPadding, lv_coord_t horizontalPadding);
	~PropertyDrawer();
	
	ePropType GetPropertyType();

	bool IsDirty();

	lv_coord_t GetWidth();
	lv_coord_t GetHeight();

	void SetWidth(lv_coord_t width);
	void SetHeight(lv_coord_t height);

  private:
	DeviceConfigItem &dci;
	ePropType propertyType;
	std::string originalValue;
	lv_obj_t *propertyContainer;
	lv_coord_t horizontalPadding, verticalPadding;
	
	void createObjects(lv_obj_t *parent);
	void createBoolItems();
	void createStringItem();
	void createStringPickerItem();
	void createIntegerItem();
	void createBoundedIntegerItem();
	
	static void switch_state_change_cb(lv_event_t *evt);
	static void input_text_change_cb(lv_event_t *evt);
	static void dropdown_text_change_cb(lv_event_t *evt);
	static void slider_value_change_cb(lv_event_t *evt);
	
	InputField<std::string> *inputFieldS = NULL;
	InputField<long> *inputFieldL = NULL;
	InputField<float> *inputFieldF = NULL;
	AdvSlider<long> *sliderL = NULL;
	
	
};