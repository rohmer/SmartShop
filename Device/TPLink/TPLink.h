#pragma once

#include <string>
#include <vector>

#include "../Sensor.h"
#include "../DeviceBase.h"

#include "TPLinkAPI.h"

extern "C" DeviceBase *Factory();

class TPLink : public DeviceBase, public Sensor
{
public:	
	TPLink(
		std::string Name="TPLink Agent",
		std::string Description="Agent to connect to TPLink Devices",
		int PolllingInterval=300);

	
	TPLink(DeviceConfig dc);
	
	void UpdateConfig(DeviceConfig dc);
	
	std::vector<SensorEvent> PollSensor() override;
		
private:
	Logger *log;
	std::vector<std::shared_ptr<TPLink_Device>> tpLinkDevices;
};
