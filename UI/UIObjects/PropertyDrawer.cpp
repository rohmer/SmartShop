#include "PropertyDrawer.h"

PropertyDrawer::PropertyDrawer(
	DeviceConfigItem &deviceConfigItem, 
	lv_obj_t *parent, 
	lv_coord_t horizontalPadding, 
	lv_coord_t verticalPadding) :
dci(deviceConfigItem),
								  horizontalPadding(horizontalPadding),
								  verticalPadding(verticalPadding)
																																				 
{
	createObjects(parent);
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

void PropertyDrawer::SetWidth(lv_coord_t width)
{
	lv_obj_set_width(propertyContainer, width);
}

void PropertyDrawer::SetHeight(lv_coord_t height)
{
	lv_obj_set_height(propertyContainer, height);
}

lv_coord_t PropertyDrawer::GetWidth()
{
	return lv_obj_get_width(propertyContainer);
}

lv_coord_t PropertyDrawer::GetHeight()
{
	return lv_obj_get_height(propertyContainer);
}

void PropertyDrawer::createObjects(lv_obj_t *parent)
{
	if (propertyContainer != NULL)
	{
		return;
	}

	propertyContainer = lv_obj_create(parent);
	switch (dci.GetDataType())
	{
	case C_BOOL:
		createBoolItems();
		break;
	case C_STR:
		createStringItem();
		break;
	case C_LONG:
		createIntegerItem();
		break;
	}
}

void PropertyDrawer::createIntegerItem()
{
	if (dci.GetLongMax() != std::numeric_limits<long>::max() && dci.GetLongMin() != std::numeric_limits<long>::min())
	{
		createBoundedIntegerItem();
		propertyType = PropertyDrawer::INT_BOUNDED_TYPE;
		return;
	}
	propertyType = PropertyDrawer::INT_PROP;
	inputFieldL = new InputField<long>(propertyContainer, dci.GetLongVal(), 0, 0, 200, lv_font_default()->line_height + 4);
	lv_obj_add_event_cb(inputFieldL->GetObject(), input_text_change_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
	lv_obj_set_height(propertyContainer, inputFieldL->GetHeight() + verticalPadding);
	lv_obj_set_width(propertyContainer, inputFieldL->GetWidth() + horizontalPadding);
	lv_obj_center(inputFieldL->GetObject());
}

void PropertyDrawer::createBoundedIntegerItem()
{
	long max = dci.GetLongMax();
	long min = dci.GetLongMin();
	long step = dci.GetLongStep();
	long value = dci.GetLongVal();
	sliderL = new AdvSlider<long>(
		propertyContainer, 
		300, 
		lv_font_default()->line_height + 4, 
		&value, 
		min, 
		max, 
		AdvSlider<long>::RIGHT_MID_VALUE_POS, 
		true, 
		step);
	lv_obj_add_event_cb(sliderL->GetSlider(), slider_value_change_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
	lv_obj_set_height(propertyContainer, sliderL->GetHeight() + verticalPadding);
	lv_obj_set_width(propertyContainer, sliderL->GetWidth() + horizontalPadding);
	lv_obj_center(sliderL->GetSlider());
}

void PropertyDrawer::createStringItem()
{
	if (dci.GetLegalStringValues().size() > 0)
	{
		createStringPickerItem();
		propertyType = PropertyDrawer::ENUM_STRING_PROP;
		return;
	}

	propertyType = PropertyDrawer::STRING_PROP;
	inputFieldS = new InputField<std::string>(propertyContainer, dci.GetStringVal(), 0, 0, 200, lv_font_default()->line_height + 4);
	lv_obj_add_event_cb(inputFieldS->GetObject(), input_text_change_cb, LV_EVENT_VALUE_CHANGED, (void *)this);
	lv_obj_set_height(propertyContainer, inputFieldS->GetHeight() + verticalPadding);
	lv_obj_set_width(propertyContainer, inputFieldS->GetWidth() + horizontalPadding);
	lv_obj_center(inputFieldS->GetObject());
}

void PropertyDrawer::createStringPickerItem()
{
	lv_obj_t *sObj = lv_dropdown_create(propertyContainer);
	std::stringstream ss;
	uint maxWidth = 0;
	int selected = -1;
	for (int i = 0; i < dci.GetLegalStringValues().size(); i++)
	{
		ss << dci.GetLegalStringValues()[i] << "\n";
		maxWidth = std::max(maxWidth, dci.GetLegalStringValues()[i].size());
		if (std::strcmp(dci.GetLegalStringValues()[i].c_str(), dci.GetStringVal().c_str()) == 0)
			selected = i;
	}
	lv_obj_set_width(sObj, lv_font_default()->line_height * (maxWidth + 2));
	lv_dropdown_set_options(sObj, ss.str().c_str());
	if (selected != -1)
		lv_dropdown_set_selected(sObj, selected);
	lv_obj_set_height(propertyContainer, lv_obj_get_height(sObj) + verticalPadding);
	lv_obj_set_width(propertyContainer, lv_obj_get_width(sObj) + horizontalPadding);
	lv_obj_center(inputFieldS->GetObject());
	lv_obj_center(sObj);
}

void PropertyDrawer::createBoolItems()
{
	// This one is fairly simple, on off swtich
	lv_obj_t *sObj=lv_switch_create(propertyContainer);
	if (dci.GetBoolVal())
		lv_obj_add_state(sObj, LV_STATE_CHECKED);
	else
		lv_obj_clear_state(sObj, LV_STATE_CHECKED);
	propertyType = PropertyDrawer::BOOL_PROP;
	lv_obj_add_event_cb(sObj, switch_state_change_cb,LV_EVENT_VALUE_CHANGED, (void *) this);
	lv_obj_set_size(sObj, 50, 30);
	lv_obj_set_height(propertyContainer, lv_obj_get_height(sObj) + verticalPadding);
	lv_obj_set_width(propertyContainer, lv_obj_get_width(sObj) + horizontalPadding);
	lv_obj_center(sObj);
}

void PropertyDrawer::input_text_change_cb(lv_event_t *evt)
{
	lv_obj_t *obj = lv_event_get_target(evt);
	PropertyDrawer *pd = (PropertyDrawer *)lv_event_get_user_data(evt);
	switch (pd->dci.GetDataType())
	{
	case C_BOOL:
		break;
	case C_STR:
		pd->dci.SetValue(lv_textarea_get_text(obj));
		break;
	case C_LONG:
		pd->dci.SetValue(std::atol(lv_textarea_get_text(obj)));
		break;
	case C_FLOAT:
		pd->dci.SetValue((float)std::atof(lv_textarea_get_text(obj)));
		break;
	case C_ARRAY:
		break;
	}
}

void PropertyDrawer::slider_value_change_cb(lv_event_t *evt)
{
	lv_obj_t *obj = lv_event_get_target(evt);
	PropertyDrawer *pd = (PropertyDrawer *)lv_event_get_user_data(evt);
	switch (pd->dci.GetDataType())
	{
	case C_BOOL:
		break;
	case C_STR:
		break;
	case C_ARRAY:
		break;
	case C_LONG:
		// Need to process this
		pd->dci.SetValue(pd->sliderL->GetValue());
		break;
	case C_FLOAT:
		pd->dci.SetValue(pd->sliderL->GetValue());
		break;
	}
}

void PropertyDrawer::switch_state_change_cb(lv_event_t *evt)
{
	lv_obj_t *obj = lv_event_get_target(evt);
	PropertyDrawer *pd = (PropertyDrawer *)lv_event_get_user_data(evt);
	if (lv_obj_has_state(obj, LV_STATE_CHECKED))
		pd->dci.SetValue(true);
	else
		pd->dci.SetValue(false);
}

void PropertyDrawer::dropdown_text_change_cb(lv_event_t *evt)
{
	lv_obj_t *obj = lv_event_get_target(evt);
	PropertyDrawer *pd = (PropertyDrawer *)lv_event_get_user_data(evt);
	std::vector<std::string> options = pd->dci.GetLegalStringValues();
	int sIdx = lv_dropdown_get_selected(obj);
	if (sIdx != -1)
	{
		pd->dci.SetValue(options[sIdx]);
	}
}