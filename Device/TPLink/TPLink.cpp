#include "TPLink.h"

TPLink::TPLink(
	std::string Name,
	std::string Description,
	unsigned int PollingInterval)
	: DeviceBase(Name, Description, eDeviceType::SENSOR, eDeviceBus::NA, PollingInterval)
{
}

TPLink::TPLink(DeviceConfig dc) :
	DeviceBase(
		"TPLink Agent",
		"Agent to connect to TPLink Devices",
	eDeviceType::SENSOR,
	eDeviceBus::NA,
	30)
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
	if (dc.HasConfigItem("devices"))
	{
		DeviceConfigItem devicesDCI = dc.GetConfigItem("devices");
		if (devicesDCI.GetDataType() != eConfigDataType::C_ARRAY)
		{
			log->LogC("Devices config item is not the right format, recreating");
			dc.DeleteConfigItem("devices");
			std::vector<DeviceConfigItem> devices;
			dc.AddConfigItem(DeviceConfigItem("devices", devices, false));
		}
		else
		{
			for (std::vector<DeviceConfigItem>::iterator it = devicesDCI.GetArrayValues().begin();
				it != devicesDCI.GetArrayValues().end();
				++it)
			{
				if (it->GetDataType() == eConfigDataType::C_ARRAY)
				{
					eTPLinkDeviceType deviceType;
					std::string ipAddr;
					for (std::vector<DeviceConfigItem>::iterator it2 = it->GetArrayValues().begin();
						it2 != it->GetArrayValues().end();
						++it)
					{
						if(strcmp(it2->GetName().c_str(), "ipaddr")==0)
							{
								ipAddr = it2->GetStringVal();
							}
						if (strcmp(it2->GetName().c_str(), "devType") == 0)
						{
							deviceType = (eTPLinkDeviceType)it2->GetLongVal();
						}
						tpLinkDevices.push_back(sTPLinkIOTDevice(ipAddr, deviceType));
					}
				}
			}
		}
	}
}