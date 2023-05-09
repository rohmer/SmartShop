#pragma once

#include <string>
#include <lvgl.h>
#include "../../Logger/Logger.h"
#include "../../Device/DeviceConfigItem.h"

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
	
	PropertyDrawer(DeviceConfigItem &deviceConfigItem, lv_obj_t *parent);
	~PropertyDrawer();
	
	ePropType GetPropertyType();

	bool IsDirty();
	
	

  private:
	DeviceConfigItem dci;
	ePropType propertyType;
	std::string originalValue;
	
	void draw(lv_obj_t *parent);

	lv_obj_t *propertyContainer;
};