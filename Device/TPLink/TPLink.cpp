#include "TPLink.h"

TPLink::TPLink(
	std::string Name,
	std::string Description,
	int PollingInterval)
	: DeviceBase(Name, Description, eDeviceType::GENERIC, eDeviceBus::NA, PollingInterval),
	Sensor()
{
}

TPLink::TPLink(DeviceConfig dc) :
	DeviceBase(
		"TPLink Agent",
		"Agent to connect to TPLink Devices",
	eDeviceType::SENSOR,
	eDeviceBus::NA,
	30),
	Sensor()
	
{
	UpdateConfig(dc);
}

void TPLink::UpdateConfig(DeviceConfig dc)
{
	if (dc.HasConfigItem("name"))
		name = dc.GetName();
	if (dc.HasConfigItem("desc"))
		desc = dc.GetDescription();
	if (dc.HasConfigItem("PollingInterval"))
		SetPollingInterval(dc.GetConfigItem("PollingInterval").GetLongVal());
	
}