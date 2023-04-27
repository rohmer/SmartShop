#pragma once

#include <string>

#include <lvgl.h>

class CollapsableWindow
{
  public:
	CollapsableWindow(
		lv_obj_t *parent, 
		std::string WindowTitle, 
		uint TitleBarSize = 50, 
		bool hasCloseBtn=true,
		bool animatedTransitions=true);
	CollapsableWindow(
		lv_obj_t *parent, 
		std::string WindowTitle, 
		uint width, 
		uint height, 
		uint titleBarSize, 
		bool hasCloseBtn = true,
		bool antimatedTransitions=true);
	lv_obj_t *getWindowContainer();
	~CollapsableWindow();

	void CollapseWindow();
	void OpenWindow();
	bool GetWindowState();
	

  private:
	lv_obj_t *windowObject;
	lv_obj_t *windowContent, *windowTitle, *closeBtn, *directionPtr;
	bool isExpanded = true;
	bool animatedTransitions = false;
	uint windowOpenHeight;
	static void headerClicked(lv_event_t *e);
	static void setWindowHeight(void *var, int32_t v);
};