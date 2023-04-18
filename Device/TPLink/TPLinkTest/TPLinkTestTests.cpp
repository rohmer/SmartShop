

#include "../TPLinkAPI.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>
/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

TEST_GROUP(TPLinkAPI_Discovery)
{
};

TEST(TPLinkAPI_Discovery, TestDiscovery)
{
	TPLinkAPI tplinkApi;
	std::vector<sTPLinkIOTDevice> devices = tplinkApi.Discovery(30);   
}
