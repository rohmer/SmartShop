#include "TAConfig.h"

TAConfig::TAConfig()
{
	dc = DeviceConfig("Telemetry Agent", "Configuration for the Telemetry Agent", eDeviceBus::NA, SENSOR);
	dc.AddConfigItem(DeviceConfigItem("Enabled", true));
	dc.AddConfigItem(DeviceConfigItem("TempWarn", (float)50.0));
	dc.AddConfigItem(DeviceConfigItem("TempCrit", (float)60.0));
	dc.AddConfigItem(DeviceConfigItem("RootFSOnly", true));	
	dc.AddConfigItem(DeviceConfigItem("DiskPctWarn", (float)40.0));
	dc.AddConfigItem(DeviceConfigItem("DiskPctCrit", (float)25.0));
	dc.AddConfigItem(DeviceConfigItem("PollingInterval", 300));
}
