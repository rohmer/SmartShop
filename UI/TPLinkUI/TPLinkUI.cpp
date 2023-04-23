#include "TPLinkUI.h"


void TPLinkUI::Init()
{
}

void TPLinkUI::Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
{
}


void TPLinkUI::Update()
{
}

// the class factories

extern "C" UIWidget* create() {
	return new TPLinkUI();
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}