#pragma once

#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "../Device/DeviceConfig.h"
#include "../RESTServer/RESTServer.h"

class ServerConfig
{
public:
	ServerConfig(
		uint serverPort=8080,
		uint serverThreads=16);
	
	ServerConfig(DeviceConfig dc);
	
	static ServerConfig FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfigItem> ToDeviceConfig();
	void Update(DeviceConfig devConf);
	
private:
	uint serverPort=8080;
	uint serverThreads = 16;
	
};