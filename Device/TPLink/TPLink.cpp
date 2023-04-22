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

// The only events this sends is discovery events, everything else is 
// handled by the ui

std::vector<SensorEvent> TPLink::PollSensor()
{
	TPLinkAPI api;
	std::vector<std::shared_ptr<TPLink_Device>> devList = api.Discovery();
	
	std::vector<SensorEvent> events;
	for (std::vector<std::shared_ptr<TPLink_Device>>::iterator it = devList.begin();
		it != devList.end(); ++it)
	{
		bool found = false;
		for (std::vector<std::shared_ptr<TPLink_Device>>::iterator i2 = tpLinkDevices.begin();
			i2 != tpLinkDevices.end(); ++i2)
		{
			if (strcmp(it->get()->GetHwID().c_str(), i2->get()->GetHwID().c_str()) == 0 &&
				strcmp(it->get()->GetMACAddress().c_str(), i2->get()->GetMACAddress().c_str()) == 0)
			{
				found = true;
				break;			
			}
		}
		if (!found)
		{
			std::shared_ptr<TPLink_Device> dev = *it;
			tpLinkDevices.push_back(*it);;
			SensorEvent se("TPLink", it->get()->GetIPAddress(), it->get()->GetHwID());
			se.AddEventData(IntData("Type", it->get()->GetDeviceType()));
			events.push_back(se);
		}
	}
	return events;
}