

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
	std::vector<std::shared_ptr<TPLink_Device>> devices = tplinkApi.Discovery(30);   
}

TEST_GROUP(TPLinkAPI_Commands)
{
};	

TEST(TPLinkAPI_Commands, SetAlias)
{
	TPLinkAPI tplinkApi;
	CHECK(tplinkApi.SetAlias("192.168.4.200", "NewAlias"));
}