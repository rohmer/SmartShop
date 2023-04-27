#include "CollapableWindow.h"

CollapsableWindow::CollapsableWindow(
	lv_obj_t *parent,
	std::string windowTitleTxt,
	uint titleBarSize,
	bool hasCloseBtn,
	bool animatedTransitions) : animatedTransitions(animatedTransitions)
{
	windowObject = lv_win_create(parent, titleBarSize);
	lv_obj_set_width(windowObject, 320);
	lv_obj_set_height(windowObject, 200);
	directionPtr = lv_label_create(lv_win_get_header(windowObject));
	lv_label_set_text(directionPtr, LV_SYMBOL_DOWN);
	lv_obj_set_align(directionPtr, LV_ALIGN_LEFT_MID);
	if (windowTitleTxt.length() > 0)
	{
		windowTitle = lv_obj_create(lv_win_get_header(windowObject));
		lv_label_set_text(windowTitle, windowTitleTxt.c_str());
	}
	if (hasCloseBtn)
	{
		closeBtn = lv_obj_create(lv_win_get_header(windowObject));
		lv_obj_set_align(closeBtn, LV_ALIGN_OUT_RIGHT_MID);
		lv_label_set_text(closeBtn, LV_SYMBOL_CLOSE);
	}
	lv_obj_add_flag(lv_win_get_header(windowObject), LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_event_cb(lv_win_get_header(windowObject), headerClicked, LV_EVENT_CLICKED, (void *)this);
	windowOpenHeight = lv_obj_get_height(lv_win_get_content(windowObject));
}

CollapsableWindow::CollapsableWindow(
	lv_obj_t *parent,
	std::string windowTitleTxt,
	uint width,
	uint height,
	uint titleBarSize,
	bool hasCloseBtn,
	bool animatedTranistions) : animatedTransitions(animatedTranistions)
{
	windowObject = lv_win_create(parent, titleBarSize);
	directionPtr = lv_label_create(lv_win_get_header(windowObject));
	lv_label_set_text(directionPtr, LV_SYMBOL_DOWN);
	lv_obj_set_align(directionPtr, LV_ALIGN_LEFT_MID);
	if (windowTitleTxt.length() > 0)
	{
		windowTitle = lv_obj_create(lv_win_get_header(windowObject));
		lv_label_set_text(windowTitle, windowTitleTxt.c_str());
	}
	if (hasCloseBtn)
	{
		closeBtn = lv_obj_create(lv_win_get_header(windowObject));
		lv_obj_set_align(closeBtn, LV_ALIGN_OUT_RIGHT_MID);
		lv_label_set_text(closeBtn, LV_SYMBOL_CLOSE);
	}
	lv_obj_add_flag(lv_win_get_header(windowObject), LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_event_cb(lv_win_get_header(windowObject), headerClicked, LV_EVENT_CLICKED, (void *)this);
	lv_obj_set_size(windowObject, width, height);
	windowOpenHeight = lv_obj_get_height(lv_win_get_content(windowObject));
}

bool CollapsableWindow::GetWindowState()
{
	return isExpanded;
}

void CollapsableWindow::setWindowHeight(void *var, int32_t v)
{
	lv_obj_set_height((lv_obj_t*)var, v);
}

void CollapsableWindow::CollapseWindow()
{
	lv_anim_t a;
	lv_anim_init(&a);
	lv_anim_set_var(&a, windowContent);
	lv_anim_set_values(&a, lv_obj_get_height(windowContent), 0);
	lv_anim_set_time(&a, 300);
	lv_anim_set_exec_cb(&a, setWindowHeight);
	lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
	lv_anim_start(&a);
	lv_label_set_text(directionPtr, LV_SYMBOL_DOWN);
}

void CollapsableWindow::OpenWindow()
{
	lv_anim_t a;
	lv_anim_init(&a);
	lv_anim_set_var(&a, windowContent);
	lv_anim_set_values(&a, 0, windowOpenHeight);
	lv_anim_set_time(&a, 300);
	lv_anim_set_exec_cb(&a, setWindowHeight);
	lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
	lv_anim_start(&a);
	lv_label_set_text(directionPtr, LV_SYMBOL_DOWN);
}
void CollapsableWindow::headerClicked(lv_event_t *e)
{
	lv_obj_t *header;
	CollapsableWindow *cw = static_cast<CollapsableWindow*>(e->user_data);
	
	if(cw->GetWindowState())
	{
		// We are open, lets close it
		cw->CollapseWindow();
		return;
	}	
	cw->OpenWindow();
}