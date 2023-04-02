#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <lvgl.h>

class ListBox
{
  public:
	ListBox(
		lv_obj_t *parent, 
		uint x,
		uint y,
		std::vector<std::string> options, 
		uint selected = 0, 
		uint menuDir=LV_DIR_BOTTOM);
	ListBox(lv_obj_t *parent,
			uint x,
			uint y,
			std::string label, 
			lv_align_t labelAlignment, 
			std::vector<std::string> options, 
			uint selected = 0, 
			uint menuDir = LV_DIR_BOTTOM);

	~ListBox();
	
	uint GetSelectedIndex();
	std::string GetSelected();
	void AddOption(std::string option, uint position);
	void ClearOptions();
	void SetOptions(std::vector<std::string> options);

  private:
	lv_obj_t *listBoxObj = NULL, *labelObj = NULL;
};