#pragma once

#include <string>
#include <vector>

#include "cJSON/cJSON.h"
#include "../Device/DeviceConfig.h"

class DBConfig
{
public:
	DBConfig(ulong maxLogSize = 52428800, ulong maxSensorSize = 524288000);
	
	static DBConfig FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfigItem> ToDeviceConfig();
	void Update(DeviceConfig dc);
	
private:
	ulong maxLogSize = 52428800;
	ulong maxSensorSize = 524288000;
};
	