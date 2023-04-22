#include "TPLinkUI.h"





// the class factories

extern "C" UIWidget* create() {
	return new TPLinkUI();
}

extern "C" void destroy(UIWidget* p) {
	delete p;
}