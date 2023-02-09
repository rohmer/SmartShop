#include "StatusWidget.h"

void StatusWidget::Init()
{
}

void StatusWidget::createObjects(lv_obj_t *parent)
{
	baseObject = lv_obj_create(parent);
}

void StatusWidget::Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
	if (baseObject == nullptr)
	{
		createObjects(parent);
	}
	lv_obj_set_width(baseObject, width);
	lv_obj_set_height(baseObject, height);
	lv_obj_set_pos(baseObject, x, y);
}

// the class factories

extern "C" UIWidget* create() {
	return new StatusWidget();
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}