#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "LogConfig.h"
#include "ServerConfig.h"
#include "DBConfig.h"
#include "Caps.h"
#include "TelemetryAgentConfig.h"
#include "../Device/DeviceConfig.h"
#include "../RaspUtils/JSON.h"

#include "../Logger/Logger.h"

class Config
{
public:
	Config();
	bool LoadConfig(std::string configFile="config.json");
	bool SaveConfig(std::string configFiles="config.json");
	
	DeviceConfig GetLogConfig();
	DeviceConfig GetServerConfig();
	DeviceConfig GetDBConfig();
	DeviceConfig GetCapsConfig();
	DeviceConfig GetTelemetryAgentConfig();
private:
	LogConfig logConfig;
	ServerConfig serverConfig;
	DBConfig dbConfig;
	Caps caps;
	TelemetryAgentConfig taConfig;
};