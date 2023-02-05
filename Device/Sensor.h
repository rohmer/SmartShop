#pragma once
#include <string>
#include "DeviceConfig.h"
#include "../SensorEvent/SensorEvent.h"

class Sensor
{
public:
	
	Sensor(uint16_t PollingIntervalInSeconds, DeviceConfig &deviceConfig)
		: deviceConfig(deviceConfig)
	{
		SetPollingInterval(PollingIntervalInSeconds);
	}
	
	virtual std::vector<SensorEvent> PollSensor()
	{
	}
	
	void SetPollingInterval(uint16_t interval)
	{
		pollingInterval = interval;
		if (deviceConfig.HasConfigItem("pollingInterval"))
		{
			DeviceConfigItem dci = deviceConfig.GetConfigItem("pollingInterval");
			dci.SetValue((long)interval);
			deviceConfig.SetConfigItem(dci);
		}
		else
		{
			DeviceConfigItem dci("pollingInterval", (long)pollingInterval);
			deviceConfig.AddConfigItem(dci);
		}
	}
	
	uint16_t GetPollingInterval()
	{
		return pollingInterval;
	}
		
protected:
	uint16_t pollingInterval;
	DeviceConfig deviceConfig;
};