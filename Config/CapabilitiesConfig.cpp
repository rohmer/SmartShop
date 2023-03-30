#include "CapabilitiesConfig.h"

CapabilitiesConfig::CapabilitiesConfig()
{
	dc = DeviceConfig("Capabilties Config", 
		"Configruration of the capabilties of this device",
		eDeviceBus::NA,
		eDeviceType::GENERIC);
	dc.AddConfigItem(DeviceConfigItem("UI", false));
	dc.AddConfigItem(DeviceConfigItem("SERVER", false));
	dc.AddConfigItem(DeviceConfigItem("CLIENT", false));
	
}

