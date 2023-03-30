#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cJSON/cJSON.h"
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
	
	void AddDeviceConfig(DeviceConfig dc);
		
	bool LoadConfig(std::string configFile="config.json");
	bool SaveConfig(std::string configFile="");
	
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
	
private:
	static Config *instance;
	Config() noexcept;
	std::string confFile;
	
	std::map<std::string, DeviceConfig> configs;
};