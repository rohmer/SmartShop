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
	
	void Init() override;
	
	void Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y) override;

private:
	void createObjects(lv_obj_t *parent, bool isMaximized);
	std::string hostname;
};