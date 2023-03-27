#pragma once 
#include <string>

#include "../Logger/Logger.h"
#include "../Device/DeviceManager.h"
#include "../Device/DeviceConfig.h"
#include "../Device/TelemetryAgent/TelemetryAgent.h"

class TelemetryAgentConfig
{
public:
	TelemetryAgentConfig(uint PollingInterval=300, 
		float TempWarn=50.0,
		float TempCrit=60.0,
		float DiskWarn=50.0,
		float DiskCrit=20.0,
		bool OnlyReportRootFS=true);
	
	static TelemetryAgentConfig FromJSON(cJSON *json);
	cJSON *ToJSON();
	
	std::vector<DeviceConfigItem> ToDeviceConfig();
	static TelemetryAgentConfig FromDeviceConfig(DeviceConfig dc);
	
	void Update();
	
private:
	uint pollingInt;
	float tempWarn, tempCrit, diskWarn, diskCrit, onlyRootFS;
	
};