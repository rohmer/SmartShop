#include "StatusWidget.h"

void StatusWidget::Init()
{
	char host[1024];
	gethostname(host, 1024);
	hostname=host;
}

void StatusWidget::createObjects(lv_obj_t *parent, bool isMaximized)
{
	if (isMaximized)
	{
		baseObject = lv_win_create(parent, 12);
		if (minBtnTxt)
			lv_obj_del(minBtnTxt);
		if (minButton)
			lv_obj_del(minButton);
	}
	else
	{
		baseObject = lv_obj_create(parent);
		minButton = lv_btn_create(baseObject);
		minBtnTxt = lv_label_create(minButton);
		lv_label_set_text(minBtnTxt, LV_SYMBOL_SETTINGS "Settings");
	}
}

void StatusWidget::Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
	if (baseObject == nullptr)
	{
		createObjects(parent, isMaximized);
	}
	lv_obj_set_width(baseObject, width);
	lv_obj_set_height(baseObject, height);
	lv_obj_set_pos(baseObject, x, y);
	
	// Get status messages for last hour
	time_t ltime = time(NULL) - 3600;
	using namespace sqlite_orm; 
	std::vector<LogMsg> messages=DB::GetInstance()->GetStorage()->get_all<LogMsg>(where(c(&LogMsg::Host) == hostname) and(c(&LogMsg::Timestamp) > ltime));
	int sev = 0;
	for (std::vector<LogMsg>::iterator it = messages.begin();
		it != messages.end();
		++it)
	{
		if (it->Severity > sev)
			sev = it->Severity;
	}
	lv_color_t bgColor = lv_palette_main(LV_PALETTE_GREEN);
	if (sev == 1)
		bgColor = lv_palette_main(LV_PALETTE_YELLOW);
	if (sev >= 2)
		bgColor = lv_palette_main(LV_PALETTE_RED);
	
	if (!isMaximized)
	{
		static lv_style_t style_btn;
		lv_style_init(&style_btn);
		lv_style_set_bg_color(&style_btn, bgColor);
		lv_obj_add_style(minButton, &style_btn,0);
	}
	
}

// the class factories

extern "C" UIWidget* create() {
	return new StatusWidget();
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}