#include "MinimizableWindow.h"

MinimizableWindow::MinimizableWindow(std::string title,
									 int x,
									 int y,
									 int width,
									 int height,
									 lv_obj_t *parent,
									 bool hasCloseBtn,
									 int iconX,
									 int iconY,
									 int iconWidth,
									 int iconHeight)
{
	if (parent == nullptr)
		parent = lv_scr_act();
	windowObject = lv_win_create(parent, 50);
	lv_obj_set_size(windowObject, width, height);
	lv_obj_set_pos(windowObject, x, y);
	lv_win_add_title(windowObject, title.c_str());
	if (hasCloseBtn)
	{
		closeBtn = lv_win_add_btn(windowObject, LV_SYMBOL_CLOSE, 40);
		lv_obj_set_user_data(closeBtn, static_cast<MinimizableWindow *>(this));
		lv_obj_add_event_cb(closeBtn, closeCB, LV_EVENT_CLICKED, this);
	}
	minimizeButton = lv_win_add_btn(windowObject, LV_SYMBOL_DOWN, 40);
	lv_obj_set_user_data(minimizeButton, this);
	lv_obj_add_event_cb(minimizeButton, minimizeCB, LV_EVENT_CLICKED,this);

	iconObject = lv_obj_create(parent);
	lv_obj_set_size(iconObject, iconWidth, iconHeight);
	lv_obj_set_pos(iconObject, iconX, iconY);
	int titleBarSize = iconHeight / 6;
	lv_obj_t *iconTB = lv_obj_create(iconObject);
	lv_obj_set_size(iconTB, iconWidth, titleBarSize);
	lv_obj_set_user_data(iconObject, this);
	lv_obj_set_user_data(iconTB, this);
	lv_obj_add_event_cb(iconTB, maximizeCB, LV_EVENT_CLICKED, this);
	lv_obj_add_event_cb(iconObject, maximizeCB, LV_EVENT_CLICKED, this);
	lv_obj_t *minLabel = lv_label_create(iconObject);
	lv_obj_align_to(minLabel, iconObject, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_width(minLabel, iconWidth);
	lv_label_set_long_mode(minLabel, LV_LABEL_LONG_SCROLL);
	lv_label_set_text(minLabel, title.c_str());
	lv_obj_add_flag(iconObject, LV_OBJ_FLAG_HIDDEN);
}

lv_obj_t* MinimizableWindow::GetWindowObj()
{
    return windowObject;
}

void MinimizableWindow::closeCB(lv_event_t *ev)
{
	if (ev->code != LV_EVENT_CLICKED)
		return;
	MinimizableWindow* mw = static_cast<MinimizableWindow*>(ev->user_data);
    lv_obj_del_async(mw->iconObject);
    lv_obj_del_async(mw->windowObject);
}

void MinimizableWindow::maximizeCB(lv_event_t *ev)
{
	if (ev->code != LV_EVENT_CLICKED)
		return;
	MinimizableWindow* mw = static_cast<MinimizableWindow*>(ev->user_data);
	lv_obj_clear_flag(mw->windowObject, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(mw->iconObject, LV_OBJ_FLAG_HIDDEN);
	;
}

void MinimizableWindow::minimizeCB(lv_event_t *ev)
{
	if (ev->code != LV_EVENT_CLICKED)
		return;
	;
	MinimizableWindow* mw = static_cast<MinimizableWindow*>(ev->user_data);
    lv_obj_add_flag(mw->windowObject, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(mw->iconObject, LV_OBJ_FLAG_HIDDEN);;
}
