#include "DropListBox.h"

ListBox::ListBox(
	lv_obj_t *parent, 
	uint x,
	uint y,
	std::vector<std::string> options, 
	uint selected,
	uint menuDir)
{
	listBoxObj = lv_dropdown_create(parent);
	std::stringstream ss;
	for (int i = 0; options.size() - 1; i++)
	{
		ss << options[i] << "\n";
	}
	ss << options[options.size()];
	lv_dropdown_set_options(listBoxObj, ss.str().c_str());
	if (selected > options.size() - 1)
		selected = options.size() - 1;
	lv_dropdown_set_selected(listBoxObj, selected);
	lv_dropdown_set_dir(listBoxObj, menuDir);
	lv_obj_set_pos(listBoxObj, x, y);
	switch (menuDir)
	{
	case LV_DIR_BOTTOM:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_DOWN);
		break;
	case LV_DIR_LEFT:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_LEFT);
		break;
	case LV_DIR_RIGHT:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_RIGHT);
		break;
	case LV_DIR_TOP:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_UP);
		break;
	default:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_DOWN);
		break;
	}
}

ListBox::ListBox(
	lv_obj_t *parent,
	uint x,
	uint y,
	std::string label,
	lv_align_t labelAlignment,
	std::vector<std::string> options,
	uint selected,
	uint menuDir)
{
	listBoxObj = lv_dropdown_create(parent);
	std::stringstream ss;
	for (int i = 0; options.size() - 1; i++)
	{
		ss << options[i] << "\n";
	}
	ss << options[options.size()];
	lv_dropdown_set_options(listBoxObj, ss.str().c_str());
	if (selected > options.size() - 1)
		selected = options.size() - 1;
	lv_dropdown_set_selected(listBoxObj, selected);
	lv_dropdown_set_dir(listBoxObj, menuDir);
	lv_obj_set_pos(listBoxObj, x, y);
	switch (menuDir)
	{
	case LV_DIR_BOTTOM:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_DOWN);
		break;
	case LV_DIR_LEFT:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_LEFT);
		break;
	case LV_DIR_RIGHT:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_RIGHT);
		break;
	case LV_DIR_TOP:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_UP);
		break;
	default:
		lv_dropdown_set_symbol(listBoxObj, LV_SYMBOL_DOWN);
		break;
	}

	labelObj = lv_label_create(parent);
	lv_label_set_text(labelObj, label.c_str());
	lv_obj_align_to(labelObj, listBoxObj, labelAlignment, 0, 0);
}

ListBox::~ListBox()
{
	if (listBoxObj != NULL)
		lv_obj_del_async(listBoxObj);
	if (labelObj != NULL)
		lv_obj_del_async(labelObj);
}

uint ListBox::GetSelectedIndex()
{
	return lv_dropdown_get_selected(listBoxObj);
}

std::string ListBox::GetSelected()
{
	char *buf = new char(64);
	lv_dropdown_get_selected_str(listBoxObj,buf,64);
	std::string s(buf);
	delete (buf);
	return s;
}

void ListBox::AddOption(std::string option, uint pos)
{
	if (pos > lv_dropdown_get_option_cnt(listBoxObj))
		pos = LV_DROPDOWN_POS_LAST;
	lv_dropdown_add_option(listBoxObj, option.c_str(), pos);
}

void ListBox::ClearOptions()
{
	lv_dropdown_clear_options(listBoxObj);
}

void ListBox::SetOptions(std::vector<std::string> options)
{
	std::stringstream ss;
	for (int i = 0; options.size() - 1; i++)
	{
		ss << options[i] << "\n";
	}
	ss << options[options.size()];
	lv_dropdown_set_options(listBoxObj, ss.str().c_str());
}