#pragma once

#include "Settings.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <cjson/cJSON.h>

#include "DeviceConfig.h"
#include "../ZeroConf/ZeroConf.h"

class Configuration
{
public:
	static Configuration *GetInstance();
	
	bool Init();
	
	ZeroConf *GetZeroConf();
	
private:
	Configuration();
	static Configuration *instance;
	ZeroConf *zeroConf;
	void readConfig();
	
	ELogLevel logFileLevel = ELogLevel::CRITICAL, logServerLevel = ELogLevel::WARN;
};