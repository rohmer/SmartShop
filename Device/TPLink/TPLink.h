#pragma once

#include <string>
#include <vector>

#include "../Sensor.h"
#include "../DeviceBase.h"

#include "TPLinkAPI.h"

class TPLink : public DeviceBase, public Sensor
{
public:	
	TPLink(
		std::string Name="TPLink Agent",
		std::string Description="Agent to connect to TPLink Devices",
		int PolllingInterval=30);

	
	TPLink(DeviceConfig dc);
	
	void UpdateConfig(DeviceConfig dc);
	
private:
	Logger *log;
	std::vector<std::shared_ptr<TPLink_Device>> tpLinkDevices;
};
