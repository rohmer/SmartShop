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
		unsigned int PollingInterval=30);
	
	TPLink(DeviceConfig dc);
	
	void UpdateConfig(DeviceConfig dc);
	
private:
	Logger *log;
	std::vector<sTPLinkIOTDevice> tpLinkDevices;
};
