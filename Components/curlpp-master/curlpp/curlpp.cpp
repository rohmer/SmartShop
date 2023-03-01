#include "curlpp.h"

/*
	To test the library, include "curlpp.h" from an application project
	and call curlppTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

int curlppTest()
{
	return ++s_Test;
}