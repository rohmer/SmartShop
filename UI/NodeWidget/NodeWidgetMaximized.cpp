#include "NodeWidgetMaximized.h"

bool NodeWidgetMaximized::isOpen = false;

NodeWidgetMaximized::NodeWidgetMaximized(lv_obj_t *parentWindow, std::string CPUID)
	: cpuID(CPUID)
	, parentWindow(parentWindow)
{
}

NodeWidgetMaximized::~NodeWidgetMaximized()
{
	// All we have to do is delete the baseWin, lvgl will clear the rest
	lv_obj_del_async(baseWindow);
}

void NodeWidgetMaximized::event_handler(lv_event_t *e)
{
	lv_obj_t *obj = lv_event_get_target(e);
	LV_UNUSED(obj);
	isOpen = false;
}

void NodeWidgetMaximized::createObjects()
{
	baseWindow = lv_win_create(parentWindow, 50);
	lv_obj_t *winTitle = lv_label_create(lv_win_get_header(baseWindow));
	using namespace sqlite_orm;
	std::shared_ptr<DBDevice> dev = DB::GetInstance()->GetStorage()->get_pointer<DBDevice>(where(c(&DBDevice::CPUID) == cpuID));
	if (dev == NULL)
	{
		// This should never happen, we wouldnt have gotten here if it wasnt in the db
		std::stringstream ss;
		ss << "Device ID: " << cpuID << " not found in DBDevice";
		Logger::GetInstance()->LogC(ss.str());
	}
	lv_label_set_text(winTitle, dev->Hostname.c_str());
	
	lv_obj_t *closeBtn = lv_win_add_btn(baseWindow, LV_SYMBOL_CLOSE, 50);
	lv_obj_add_event_cb(closeBtn, event_handler, LV_EVENT_CLICKED, NULL);	
	isOpen = true;
	lv_obj_set_layout(baseWindow, LV_LAYOUT_FLEX);
	lv_obj_set_size(baseWindow, lv_obj_get_width(parentWindow), lv_obj_get_height(parentWindow)-50);
	lv_obj_set_align(baseWindow, LV_ALIGN_TOP_LEFT);
	lv_obj_set_align(baseWindow, LV_FLEX_FLOW_ROW);
	
	int thirds=lv_obj_get_height(lv_win_get_content(baseWindow))/3-10;
	// Top container has 3 sub containers for graphs
	topContainer = lv_obj_create(baseWindow);
	lv_obj_set_width(topContainer, lv_obj_get_width(lv_win_get_content(baseWindow)) - 10);
	lv_obj_set_height(topContainer, thirds);
	
	lv_obj_set_flex_flow(topContainer, LV_FLEX_FLOW_COLUMN);		
	topLeftPanel = lv_obj_create(topContainer);
	lv_obj_set_flex_flow(topLeftPanel, LV_FLEX_FLOW_ROW);
	topCenterPanel = lv_obj_create(topContainer);
	lv_obj_set_flex_flow(topCenterPanel, LV_FLEX_FLOW_ROW);
	topRightPanel = lv_obj_create(topContainer);
	lv_obj_set_flex_flow(topRightPanel, LV_FLEX_FLOW_ROW);
	
	// Middle container has 2 sub containers
	middleContainer = lv_obj_create(baseWindow);
	lv_obj_set_flex_flow(middleContainer, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_width(middleContainer, lv_obj_get_width(lv_win_get_content(baseWindow)) - 10);
	lv_obj_set_height(middleContainer, thirds);
	middleRowLeft = lv_obj_create(middleContainer);
	lv_obj_set_flex_flow(middleRowLeft, LV_FLEX_FLOW_ROW);
	middleRowRight = lv_obj_create(middleContainer);
	lv_obj_set_flex_flow(middleRowRight, LV_FLEX_FLOW_ROW);
	
	// Bottom row only one row
	bottomRow = lv_obj_create(baseWindow);
	lv_obj_set_flex_flow(bottomRow, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_width(topContainer, lv_obj_get_width(lv_win_get_content(baseWindow)) - 10);
	lv_obj_set_height(topContainer, thirds);
}


void NodeWidgetMaximized::Update()
{
	if (isOpen == false ||baseWindow==NULL)
	{
		createObjects();
		isOpen = true;
	}
}

void NodeWidgetMaximized::Close()
{
	lv_obj_del_async(baseWindow);
}