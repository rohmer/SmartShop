#include "../HostRegistration.h"
#include "../Device/AHTX0Sensor/AHTX0Sensor.h"
#include "../Device/PCA9685Device/PCA9685Device.h"

#include "JSON.h"
#include "CPUInfo.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

TEST_GROUP(HostRegistration)
{
	
};

TEST(HostRegistration, BasicCreation)
{
	HostRegistration hr;
	STRCMP_EQUAL(hr.GetCPUID().c_str(), CPUInfo::GetCPUID().c_str());
	STRCMP_EQUAL(hr.GetHostname().c_str(), CPUInfo::GetHostname().c_str());
	CHECK_EQUAL(hr.GetCPUCount(), CPUInfo::GetCPUCount());
	CHECK_EQUAL(hr.GetDeviceType(), CPUInfo::GetPIBoardType());
}

TEST(HostRegistration, RegistrationToJSON)
{
	HostRegistration hr;
	cJSON *json = hr.ToJSON();
	
	std::string jstr = JSON::Print(json);
	CHECK(cJSON_HasObjectItem(json, "hostname"));
	STRCMP_EQUAL(cJSON_GetObjectItem(json,"hostname")->valuestring,CPUInfo::GetHostname().c_str());
	STRCMP_EQUAL(cJSON_GetObjectItem(json, "cpuid")->valuestring, CPUInfo::GetCPUID().c_str());
	CHECK_EQUAL(cJSON_GetObjectItem(json, "cpus")->valueint, CPUInfo::GetCPUCount());
	CHECK_EQUAL(cJSON_GetObjectItem(json, "hosttype")->valueint, CPUInfo::GetPIBoardType());
	cJSON_Delete(json);
}

TEST(HostRegistration, RegistrationWithDevicesToJSON)
{
	HostRegistration hr;
	AHTX0Sensor *ahtx0Sensor = new AHTX0Sensor();
	PCA9685Device *pca9685 = new PCA9685Device();
	
	hr.AddDevice(ahtx0Sensor);
	hr.AddDevice(pca9685);
	cJSON *json = hr.ToJSON();
	std::string jstr = JSON::Print(json);
	CHECK(cJSON_HasObjectItem(json, "hostname"));
	STRCMP_EQUAL(cJSON_GetObjectItem(json, "hostname")->valuestring, CPUInfo::GetHostname().c_str());
	STRCMP_EQUAL(cJSON_GetObjectItem(json, "cpuid")->valuestring, CPUInfo::GetCPUID().c_str());
	CHECK_EQUAL(cJSON_GetObjectItem(json, "cpus")->valueint, CPUInfo::GetCPUCount());
	CHECK_EQUAL(cJSON_GetObjectItem(json, "hosttype")->valueint, CPUInfo::GetPIBoardType());
	
	
	cJSON_Delete(json);
}

TEST(HostRegistration, FromJSON)
{
	std::string jStr = "{\"hostname\":\"octopi\",\"cpuid\" :\"10000000290F4DB5\",\"cpus\" :	4,\"hosttype\" :	7,\"devices\" :[]}";
	cJSON *json = cJSON_Parse(jStr.c_str());
	HostRegistration hr = HostRegistration::FromJSON(json);
	STRCMP_EQUAL(hr.GetCPUID().c_str(), CPUInfo::GetCPUID().c_str());
	STRCMP_EQUAL(hr.GetHostname().c_str(), CPUInfo::GetHostname().c_str());
	CHECK_EQUAL(hr.GetCPUCount(), CPUInfo::GetCPUCount());
	CHECK_EQUAL(hr.GetDeviceType(), CPUInfo::GetPIBoardType());
}