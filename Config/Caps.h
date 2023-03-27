#pragma once

#include <string>
#include <cJSON.h>

#include "../Logger/Logger.h"
#include "../ZeroConf/Capabilities.h"
#include "../Device/DeviceConfig.h"

class Caps
{
public:
	Caps(bool hasClient = false, bool hasServer = false, bool hasUI = false);
	
	static Caps FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfigItem> ToDeviceConfig();
	static Caps FromDeviceConfig(DeviceConfig dc);
	
private:
	bool client, server, ui;
};
