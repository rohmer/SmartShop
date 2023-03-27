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
#include "../RaspUtils/JSON.h"

class Config
{
public:
	Config();
	bool LoadConfig(std::string configFile="config.json");
	bool SaveConfig(std::string configFiles="config.json");
	
private:
	LogConfig logConfig;
	ServerConfig serverConfig;
	DBConfig dbConfig;
};