#include "NodeWidget.h"

LV_IMG_DECLARE(harddisk)
LV_IMG_DECLARE(tempIcon)
LV_IMG_DECLARE(logfile)
	
void NodeWidget::Init()
{
}

NodeWidget::~NodeWidget()
{
	if(baseObject!=NULL)
		lv_obj_del_async(baseObject);
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
		baseObject = lv_obj_create(parent);
		lv_obj_set_layout(baseObject, LV_LAYOUT_FLEX);
		lv_obj_set_flex_flow(baseObject, LV_FLEX_FLOW_ROW);
		lv_obj_set_size(baseObject, width, height);
		lv_obj_set_align(baseObject, LV_ALIGN_TOP_LEFT);
		//lv_obj_set_pos(baseObject, x, y);
		// Set layout
		lv_obj_t *leftPanel = lv_obj_create(baseObject);
		lv_obj_set_flex_flow(leftPanel, LV_FLEX_FLOW_COLUMN);
		lv_obj_t *rightQuarterPanel = lv_obj_create(baseObject);
		lv_obj_set_size(rightQuarterPanel, horizontalQuarters*2, height);
		lv_obj_set_flex_flow(rightQuarterPanel, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_size(leftPanel, horizontalQuarters * 2, height);
		
		static lv_style_t style_shadow;
		lv_style_init(&style_shadow);
		lv_style_set_shadow_width(&style_shadow, 10);
		lv_style_set_shadow_spread(&style_shadow, 5);
		lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));
		lv_obj_add_style(baseObject, &style_shadow, 0);
		
		// TODO: Create containers to hold icon and LED for each of the visuals in the right container
		// We have 3 items, so lets set them to 3rds
		lv_obj_set_layout(rightQuarterPanel, LV_LAYOUT_GRID);
		lv_coord_t halfWidth = horizontalQuarters-30;
		static lv_coord_t column_dsc[] = { halfWidth, halfWidth, LV_GRID_TEMPLATE_LAST };
		lv_coord_t thirds = (height / 3)-30;
		static lv_coord_t row_dsc[] = { thirds, thirds, thirds, LV_GRID_TEMPLATE_LAST };
		lv_obj_set_grid_dsc_array(rightQuarterPanel, column_dsc, row_dsc);
		
		logIcon=lv_img_create(rightQuarterPanel);
		lv_obj_set_grid_cell(logIcon, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);
		logLed = lv_led_create(rightQuarterPanel);
		lv_img_set_src(logIcon, &logfile);
		lv_obj_set_grid_cell(logLed, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
		
		tempIconObject = lv_img_create(rightQuarterPanel);
		lv_obj_set_grid_cell(tempIconObject, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
		tempLed = lv_led_create(rightQuarterPanel);
		lv_img_set_src(tempIconObject, &tempIcon);
		lv_obj_set_grid_cell(tempLed, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
		
		
		hardDiskIcon = lv_img_create(rightQuarterPanel);
		lv_obj_set_grid_cell(hardDiskIcon, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);
		hardDiskLed = lv_led_create(rightQuarterPanel);
		lv_obj_set_grid_cell(hardDiskLed, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 2, 1);		
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
		lv_label_set_text(authLabel, "#00CC00 Authorized#");
	}
	else
	{
		lv_label_set_text(authLabel, "#FF3333 Not Authorized#");
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
	// First get the data from the telemetry sensor event for this node
	SensorEvent se = SensorEvent::GetLatestFromDB(hostname, "TelemetryAgent");
	if (se.GetHostname().length() != 0)
	{
		int fsPct = 150;
		int fsSev = 0;		// 0 = green, 1 yellow, 2 red
		float temp = 0;
		int tempSev = 0;
		
		
	}
	
	// Need to get the logs next and find the worst one in the past 24 hours
	
}
// the class factories

extern "C" UIWidget* create() {
	NodeWidget *nw = new NodeWidget();
	return ((UIWidget *)nw);
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}