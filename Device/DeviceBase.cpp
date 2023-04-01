#include "DeviceBase.h"

DeviceBase::DeviceBase(std::string Name, std::string Description, eDeviceType deviceType, eDeviceBus deviceBus, int pollingInterval)
	: name(Name)
	, desc(Description)
	, dType(deviceType)
	, dBus(deviceBus)
	, config(DeviceConfig(Name,Description,deviceBus,deviceType))
	, log(Logger::GetInstance())
{
	if (pollingInterval >= 0)
		SetPollingInterval(pollingInterval);
}

DeviceBase::DeviceBase(std::string Name, std::string Description, DeviceConfig deviceConfig, eDeviceType deviceType, eDeviceBus deviceBus, int pollingInterval) 
	: name(Name)
	, desc(Description)
	, dType(deviceType)
	, dBus(deviceBus)	
	, config(deviceConfig)
	, log(Logger::GetInstance())
{
	if (pollingInterval >= 0)
		SetPollingInterval(pollingInterval);
}
	
void DeviceBase::SetPollingInterval(int interval)
{
	if (config.HasConfigItem("PollingInterval"))
	{
		config.DeleteConfigItem("PollingInterval");		
		if (interval < 0)
		{
			return;
		}				
	}
	config.AddConfigItem(DeviceConfigItem("PollingInterval", interval, false));
	config.Modified = true;
}

int DeviceBase::GetPollingInterval()
{
	if (config.HasConfigItem("PollingInterval"))
		return config.GetConfigItem("PollingInterval").GetLongVal();
	return -1;
}

std::string DeviceBase::GetName()
{
	return name;
}

std::string DeviceBase::GetDescription()
{
	return desc;
}

eDeviceType DeviceBase::GetType()
{
	return dType;
}

eDeviceBus DeviceBase::GetBus()
{
	return dBus;
}

DeviceConfig DeviceBase::GetConfig()
{
	return config;
}

void DeviceBase::SetConfig(DeviceConfig &deviceConfig)
{
	config = deviceConfig;
	config.Modified = true;
}

// This is used to take care of pollingInterval so each sensor doesnt have to
void DeviceBase::UpdateConfig(DeviceConfig newConfig)
{
	if (dType != eDeviceType::SENSOR)
		return;
	if (newConfig.HasConfigItem("PollingInterval"))
	{
		int poll = newConfig.GetConfigItem("PollingInterval").GetLongVal();
		SetPollingInterval(poll);
	}
}