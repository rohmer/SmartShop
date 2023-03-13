#pragma once
#include <string>

#include "DeviceEnums.h"
#include "DeviceConfig.h"
#include "../Logger/Logger.h"

class DeviceBase
{
public:
	DeviceBase(std::string Name, std::string Description, eDeviceType deviceType = eDeviceType::GENERIC, eDeviceBus deviceBus = eDeviceBus::NA, int pollingInterval=-1);
	DeviceBase(std::string Name, std::string Description, DeviceConfig deviceConfig, eDeviceType deviceType = eDeviceType::GENERIC, eDeviceBus deviceBus = eDeviceBus::NA, int pollingInterval = -1);
	
	virtual bool Init() 
	{
		return true;
	}
	
	std::string GetName();
	std::string GetDescription();
	eDeviceType GetType();
	eDeviceBus GetBus();
	DeviceConfig GetConfig();
	void SetConfig(DeviceConfig &deviceConfig);
	
	void SetPollingInterval(int val);
	int GetPollingInterval();

	virtual void UpdateConfig(DeviceConfig newConfig);
	
protected:
	DeviceConfig config;
	std::string name, desc;
	eDeviceType dType;
	eDeviceBus dBus;	
	Logger *log;
	int pollingInterval;
};