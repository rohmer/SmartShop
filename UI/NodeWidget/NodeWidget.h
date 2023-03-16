#include <unistd.h>

#include <lvgl.h>
#include "../../DB/DB.h"
#include "../../Logger/LogMsg.h"

#include "../UIWidget/UIWidget.h"
extern "C" UIWidget *Factory();

class NodeWidget : public UIWidget
{
public:
	NodeWidget()
		: UIWidget("ALL", "Status")
	{
	}
	~NodeWidget();
	
	void Init() override;
	
	void Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y) override;
	void SetID(std::string id);
	
private:
	void createObjects(lv_obj_t *parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y);
	std::string hostname;
	std::string ipAddr;
	std::string hostID;
	bool authorized;
	int deviceType, cpuCount;
	lv_obj_t *nodeWidgetContainer;
	
	lv_obj_t *hardDiskIcon, *hardDiskLed;
	lv_obj_t *logIcon, *logLed;
	lv_obj_t *tempIconObject, *tempLed;
	lv_obj_t *hostnameLabel, *ipLabel, *cpuCountLabel, *deviceTypeLabel, *authLabel;
	void drawIcon();
	void drawMaximixed();
	
	
	uint width, height, verticalQuarters, horizontalQuarters;
};