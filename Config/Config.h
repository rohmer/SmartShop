#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "../Device/DeviceManager.h"
#include "../Device/DeviceConfig.h"
#include "../RaspUtils/JSON.h"

#include "../Logger/Logger.h"

#include "CapabilitiesConfig.h"
#include "LogConfig.h"
#include "RESTConfig.h"
#include "DBConfig.h"
#include "TAConfig.h"

class Config
{
public:
	
	enum EConfigSetResult
	{
		eSUCCESS,
		eREADONLY,
		eVARIABLEDOESNOTEXIST,
		eCONFIGDOESNOTEXIST
	};
	
	static Config *GetInstance();
	Config();
	void AddDeviceConfig(DeviceConfig dc);
	void AddDeviceConfigs(DeviceManager *dm=NULL);
	
	bool LoadConfig(std::string configFile="config.json");
	bool SaveConfig(std::string configFile="config.json");
	
	DeviceConfig GetLogConfig()
	{
		return configs[LogConfig::GetName()];
	}
	DeviceConfig GetServerConfig()
	{
		return configs[RESTConfig::GetName()];
	}
	DeviceConfig GetDBConfig()
	{
		return configs[DBConfig::GetName()];
	}
	DeviceConfig GetCapsConfig()
	{
		return configs[CapabilitiesConfig::GetName()];
	}
	DeviceConfig GetTelemetryAgentConfig()
	{
		return configs[TAConfig::GetName()];
	}

	std::vector<std::string> GetRestLogServers();
	void AddRestLogServer(std::string server);
	void RemoveRestLogServer(std::string server);
	void ClearRestLogServers();

	EConfigSetResult SetConfigVariable(std::string ConfigName, std::string VariableName, std::string value);
	
	static Config FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfig> GetDevices();
	
	DeviceConfig GetDeviceConfig(std::string name);

private:
	static Config *instance;
	std::string confFile;
	
	std::map<std::string, DeviceConfig> configs, devices;
};