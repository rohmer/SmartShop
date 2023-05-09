#include "PropertyDrawer.h"

PropertyDrawer::PropertyDrawer(DeviceConfigItem &deviceConfigItem, lv_obj_t *parent) : dci(deviceConfigItem)
{
	draw(parent);
}

PropertyDrawer::~PropertyDrawer()
{
	if (propertyContainer != NULL)
	{
		lv_obj_del(propertyContainer);
		return;
	}
	#ifdef DEBUG
	Logger::GetInstance()->LogW("Property Drawer did not have a display object");
	#endif
}

void PropertyDrawer::draw(lv_obj_t *parent)
{
	if (propertyContainer != NULL)
	{
		return;
	}

	propertyContainer = lv_obj_create(parent);
	
}