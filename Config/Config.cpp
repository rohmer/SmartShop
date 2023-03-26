#include "Config.h"

/*
	To test the library, include "Config.h" from an application project
	and call ConfigTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

int ConfigTest()
{
	return ++s_Test;
}