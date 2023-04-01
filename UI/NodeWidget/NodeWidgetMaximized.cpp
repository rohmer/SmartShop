#include "NodeWidgetMaximized.h"

bool NodeWidgetMaximized::isOpen = false;

NodeWidgetMaximized::NodeWidgetMaximized(lv_obj_t *parentWindow, std::string CPUID)
	: cpuID(CPUID)	
{
	baseWindow = lv_win_create(parentWindow, 50);
	lv_obj_t *winTitle = lv_label_create(lv_win_get_header(baseWindow));
	using namespace sqlite_orm;
	std::shared_ptr<DBDevice> dev = DB::GetInstance()->GetStorage()->get_pointer<DBDevice>(where(c(&DBDevice::CPUID) == CPUID));
	if (dev == NULL)
	{
		// This should never happen, we wouldnt have gotten here if it wasnt in the db
		std::stringstream ss;
		ss << "Device ID: " << CPUID << " not found in DBDevice";
		Logger::GetInstance()->LogC(ss.str());
	}
	lv_label_set_text(winTitle, dev->Hostname.c_str());
	
	lv_obj_t *closeBtn=lv_win_add_btn(baseWindow, LV_SYMBOL_CLOSE, 50);
	lv_obj_add_event_cb(closeBtn, event_handler, LV_EVENT_CLICKED, NULL);	
	isOpen = true;
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

void NodeWidgetMaximized::Update()
{
	
}