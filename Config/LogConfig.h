#pragma once

#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "../Logger/Logger.h"
#include "../Device/DeviceConfig.h"

class LogConfig
{
public:
	LogConfig()
	{
	}
		
	LogConfig(bool useSTDIO,
		ELogLevel stdioLevel,
		bool useREST,
		ELogLevel restLevel,
		bool useDB,
		ELogLevel dbLevel,
		std::vector<std::string> restServers,
		uint restServerPort);
	
	static LogConfig FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfigItem> ToDeviceConfig();
	
	void Update(DeviceConfig deviceConfig);
	
private:
#ifdef DEBUG
	bool useSTDIO = true;
	ELogLevel stdioLevel = ELogLevel::INFO;
#else
	bool useSTDIO = false;
	ELogLevel stdioLevel = ELogLevel::WARN;
#endif

#ifdef CLIENT
	bool useRESTLog = true;
	ELogLevel restLogLevel = ELogLevel::WARN;
	std::vector<std::string> restServers;
	uint restServerPort = 8080;
#else
	bool useRESTLog = false;	
	std::vector<std::string> restServers;
	uint restServerPort = 8080;
	#ifdef DEBUG
		ELogLevel restLogLevel = ELogLevel::INFO;
	#else
		ELogLevel restLogLevel = ELogLevel::WARN;
	#endif
#endif
	
#ifdef SERVER
	bool useDBLog = true;
#else
	bool useDBLog = false;
#endif
#ifdef DEBUG
	ELogLevel dbLogLevel = ELogLevel::INFO;
#else
	ELogLevel dbLogLevel = ELogLevel::WARN;
#endif			
};