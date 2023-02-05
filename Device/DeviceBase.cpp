#include "DeviceBase.h"

DeviceBase::DeviceBase(std::string Name, std::string Description, eDeviceType deviceType, eDeviceBus deviceBus)
	: name(Name)
	, desc(Description)
	, dType(deviceType)
	, dBus(deviceBus)
	, config(DeviceConfig())
	, log(Logger::GetInstance())
{
}

DeviceBase::DeviceBase(std::string Name, std::string Description, DeviceConfig deviceConfig, eDeviceType deviceType, eDeviceBus deviceBus) 
	: name(Name)
	, desc(Description)
	, dType(deviceType)
	, dBus(deviceBus)	
	, config(deviceConfig)
	, log(Logger::GetInstance())
{
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
}