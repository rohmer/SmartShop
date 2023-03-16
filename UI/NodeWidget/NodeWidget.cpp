#include "NodeWidget.h"

LV_IMG_DECLARE(harddisk)
LV_IMG_DECLARE(tempIcon)
LV_IMG_DECLARE(logfile)
	
void NodeWidget::Init()
{
}

NodeWidget::~NodeWidget()
{
	lv_obj_del_async(nodeWidgetContainer);
}

void NodeWidget::SetID(std::string id)
{
	hostID = id;
}

void NodeWidget::createObjects(lv_obj_t *parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
	if (isMaximized)
	{
		baseObject = lv_win_create(parent, 12);
		minButton = lv_win_add_btn(baseObject, LV_SYMBOL_CLOSE, 60);
		lv_obj_add_event_cb(minButton, event_cb, LV_EVENT_ALL, baseObject);
		// Display all our doo dads to display on the full screen
	}
	else
	{
		this->width = width;
		this->height = height;
		verticalQuarters = height / 4;
		horizontalQuarters = width / 4;
		nodeWidgetContainer = lv_obj_create(parent);
		baseObject = nodeWidgetContainer;
		lv_obj_set_layout(nodeWidgetContainer, LV_LAYOUT_FLEX);
		lv_obj_set_flex_flow(nodeWidgetContainer, LV_FLEX_FLOW_ROW);
		lv_obj_set_size(nodeWidgetContainer, width, height);
		lv_obj_set_align(nodeWidgetContainer, LV_ALIGN_TOP_LEFT);
		// Set layout
		lv_obj_t *leftPanel = lv_obj_create(nodeWidgetContainer);
		lv_obj_set_flex_flow(leftPanel, LV_FLEX_FLOW_COLUMN);
		lv_obj_t *rightQuarterPanel = lv_obj_create(nodeWidgetContainer);
		lv_obj_set_size(rightQuarterPanel, horizontalQuarters, height);
		lv_obj_set_flex_flow(rightQuarterPanel, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_size(leftPanel, horizontalQuarters * 3, height);
		
		static lv_style_t style_shadow;
		lv_style_init(&style_shadow);
		lv_style_set_shadow_width(&style_shadow, 10);
		lv_style_set_shadow_spread(&style_shadow, 5);
		lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));
		lv_obj_add_style(nodeWidgetContainer, &style_shadow, 0);
		
		// TODO: Create containers to hold icon and LED for each of the visuals in the right container
		// We have 3 items, so lets set them to 3rds
		int thirdHeight = this->height / 3;
		lv_obj_t *logContainer = lv_obj_create(rightQuarterPanel);
		lv_obj_set_size(logContainer, horizontalQuarters, thirdHeight);
		
		lv_obj_align(logContainer, LV_ALIGN_CENTER,0,0);
		lv_obj_set_flex_flow(logContainer, LV_FLEX_FLOW_ROW);
		logIcon=lv_img_create(logContainer);
		logLed = lv_led_create(logContainer);
		lv_img_set_src(logIcon, &logfile);
		
		lv_obj_t *tempContainer = lv_obj_create(rightQuarterPanel);
		lv_obj_set_size(tempContainer, horizontalQuarters, thirdHeight);
		lv_obj_set_flex_flow(tempContainer, LV_FLEX_FLOW_ROW);
		
		tempIconObject = lv_img_create(tempContainer);
		tempLed = lv_led_create(tempContainer);
		lv_img_set_src(tempIconObject, &tempIcon);
		
		lv_obj_t *hdContainer = lv_obj_create(rightQuarterPanel);
		lv_obj_set_size(hdContainer, horizontalQuarters, thirdHeight);
		lv_obj_set_flex_flow(hdContainer, LV_FLEX_FLOW_ROW);
		
		hardDiskIcon = lv_img_create(hdContainer);
		hardDiskLed = lv_led_create(hdContainer);
		lv_img_set_src(hardDiskIcon, &harddisk);
	
		// Since we dont have info yet, we are going to set the LEDs to Grey
		lv_led_set_color(logLed, lv_palette_main(LV_PALETTE_GREY));
		lv_led_set_color(tempLed, lv_palette_main(LV_PALETTE_GREY));
		lv_led_set_color(hardDiskLed, lv_palette_main(LV_PALETTE_GREY));
		
		hostnameLabel = lv_label_create(leftPanel);
		ipLabel = lv_label_create(leftPanel);
		cpuCountLabel = lv_label_create(leftPanel);
		deviceTypeLabel = lv_label_create(leftPanel);
		authLabel = lv_label_create(leftPanel);		
		lv_label_set_recolor(authLabel, true);
	}
	
	// Grab some things that are unlikely to change, the one variable here is if the user authorizes the node
	using namespace sqlite_orm;
	std::vector<DBDevice> dev=DB::GetInstance()->GetStorage()->get_all<DBDevice>(where(hostID == c(&DBDevice::CPUID)));
	if (dev.size() == 0)
	{
		// This should never happened because the node widget manager shouldnt have set it.
		std::stringstream ss;
		ss << "Attempting to create UI for node that doesnt exist: " << hostID;
		log->LogC(ss.str());
		return;
	}
	
	hostname = dev[0].Hostname;
	lv_label_set_text(hostnameLabel, hostname.c_str());
	ipAddr = dev[0].IPAddress;
	lv_label_set_text(ipLabel, ipAddr.c_str());
	authorized = dev[0].isAuth;
	if (authorized)
	{
		lv_label_set_text(authLabel, "#00CC00Authorized");
	}
	else
	{
		lv_label_set_text(authLabel, "#FF3333Not Authorized");
	}
	deviceType = dev[0].DeviceType;
	lv_label_set_text(deviceTypeLabel, CPUInfo::BoardTypeToString((EPIType)deviceType).c_str());
	cpuCount = dev[0].CPUCount;
	std::stringstream cpuCt;
	cpuCt << cpuCount << " CPUs";
	lv_label_set_text(cpuCountLabel, cpuCt.str().c_str());
}

void NodeWidget::Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
	if (baseObject == nullptr)
	{
		createObjects(parent, isMaximized,  width, height, x, y);
	}

	if (!isMaximized)
	{
		drawIcon();
	}
}

void NodeWidget::drawIcon()
{
	
}
// the class factories

extern "C" UIWidget* create() {
	return new NodeWidget();
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}