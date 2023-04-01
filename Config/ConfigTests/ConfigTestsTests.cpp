#include <stdio.h>
#include "../Config.h"
#include "../../RaspUtils/CPUInfo.h"
#include "../../Device/DeviceConfig.h"
#include "../../Device/TelemetryAgent/TelemetryAgent.h"
#include "../../Device/AHTX0Sensor/AHTX0Sensor.h"
#include <CppUTest/CommandLineTestRunner.h>

void CheckDefaultLogConfig(Config config)
{
	DeviceConfig dc = config.GetLogConfig();
	CHECK_EQUAL(dc.GetConfigItem("STDIO").GetBoolVal(), true);
	CHECK_EQUAL(dc.GetConfigItem("STDIOLevel").GetLongVal(), (int)ELogLevel::INFO);
	CHECK_EQUAL(dc.GetConfigItem("DB").GetBoolVal(), false);
	CHECK_EQUAL(dc.GetConfigItem("DBLevel").GetLongVal(), (int)ELogLevel::INFO);
	CHECK_EQUAL(dc.GetConfigItem("RESTLog").GetBoolVal(), false);
	CHECK_EQUAL(dc.GetConfigItem("RESTLevel").GetLongVal(), (int)ELogLevel::INFO);
	CHECK_EQUAL(dc.GetConfigItem("RESTPort").GetLongVal(), 8080);
	CHECK_EQUAL(dc.GetConfigItem("RESTServers").GetStringVal(), "");
}

void CheckDefaultCapsConfig(Config config)
{
	DeviceConfig dc = config.GetCapsConfig();
	CHECK_EQUAL(dc.GetConfigItem("UI").GetBoolVal(),false);
	CHECK_EQUAL(dc.GetConfigItem("SERVER").GetBoolVal(), false);
	CHECK_EQUAL(dc.GetConfigItem("CLIENT").GetBoolVal(), false);	
}

void CheckDefaultDBConfig(Config config)
{
	DeviceConfig dc = config.GetDBConfig();
	CHECK_EQUAL(dc.GetConfigItem("EventTableSize").GetLongVal(), 524288000);
	CHECK_EQUAL(dc.GetConfigItem("LogTableSize").GetLongVal(), 262144000);
}

void CheckDefaultRESTConfig(Config config)
{
	DeviceConfig dc = config.GetServerConfig();
	int cpuCount = CPUInfo::GetCPUCount();
	CHECK_EQUAL(dc.GetConfigItem("Threads").GetLongVal(), cpuCount * 4);
	CHECK_EQUAL(dc.GetConfigItem("Port").GetLongVal(), 8080);
}

void CheckDefaultTAConfig(Config config)
{
	DeviceConfig dc = config.GetTelemetryAgentConfig();
	CHECK_EQUAL(dc.GetConfigItem("Enabled").GetBoolVal(), true);
	CHECK_EQUAL(dc.GetConfigItem("TempWarn").GetFloatVal(), 50.0);
	CHECK_EQUAL(dc.GetConfigItem("TempCrit").GetFloatVal(), 60.0);
	CHECK_EQUAL(dc.GetConfigItem("DiskPctWarn").GetFloatVal(), 40.0);
	CHECK_EQUAL(dc.GetConfigItem("DiskPctCrit").GetFloatVal(), 25.0);
	CHECK_EQUAL(dc.GetConfigItem("RootFSOnly").GetBoolVal(), true);
	CHECK_EQUAL(dc.GetConfigItem("PollingInterval").GetLongVal(), 300);	
}

void CheckDefaults(Config config)
{
	CheckDefaultLogConfig(config);
	CheckDefaultCapsConfig(config);	
	CheckDefaultDBConfig(config);
	CheckDefaultRESTConfig(config);
	CheckDefaultTAConfig(config);
}

TEST_GROUP(ConfigTests)
{
};

TEST(ConfigTests, DefaultConstructor)
{
	Config config;
	CheckDefaults(config);
}

TEST(ConfigTests, AddDevices)
{	
	Config config;
	TelemetryAgent *ta = new TelemetryAgent();
	config.AddDeviceConfig(ta->GetConfig());
	
	// The telemetry agent is a special agent that is part of the default configuration, so adding another one here.
	AHTX0Sensor *aht = new AHTX0Sensor();
	config.AddDeviceConfig(aht->GetConfig());
	CheckDefaults(config);
	
	DeviceConfig dc = config.GetDeviceConfig(aht->GetName());
	CHECK_TRUE(dc.HasConfigItem("PollingInterval"));
	CHECK_TRUE(dc.HasConfigItem("I2C Bus"));
	CHECK_TRUE(dc.HasConfigItem("I2C Address"));
	CHECK_EQUAL(dc.GetConfigItem("PollingInterval").GetLongVal(), 300);
	CHECK_EQUAL(dc.GetConfigItem("I2C Bus").GetLongVal(), 0);
	CHECK_EQUAL(dc.GetConfigItem("I2C Address").GetLongVal(), 56);
}

TEST(ConfigTests, Serialization)
{
	Config config;
	TelemetryAgent *ta = new TelemetryAgent();
	config.AddDeviceConfig(ta->GetConfig());
	
	// The telemetry agent is a special agent that is part of the default configuration, so adding another one here.
	AHTX0Sensor *aht = new AHTX0Sensor();
	config.AddDeviceConfig(aht->GetConfig());
	CheckDefaults(config);

	cJSON *json = config.ToJSON();
	std::string jStr = JSON::Print(json);
	std::cout << jStr << "\n\n";
	Config config2 = Config::FromJSON(json);
	CheckDefaults(config2);
	DeviceConfig dc = config2.GetDeviceConfig(aht->GetName());
	CHECK_TRUE(dc.HasConfigItem("PollingInterval"));
	CHECK_TRUE(dc.HasConfigItem("I2C Bus"));
	CHECK_TRUE(dc.HasConfigItem("I2C Address"));
	CHECK_EQUAL(dc.GetConfigItem("PollingInterval").GetLongVal(), 300);
	CHECK_EQUAL(dc.GetConfigItem("I2C Bus").GetLongVal(), 0);
	CHECK_EQUAL(dc.GetConfigItem("I2C Address").GetLongVal(), 56);
}