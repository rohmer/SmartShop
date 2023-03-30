#include "RESTConfig.h"

RESTConfig::RESTConfig()
{
	dc = DeviceConfig("REST Config", 
		"Configuration for the integrated REST server in client and servers",
		NA,
		GENERIC);
	dc.AddConfigItem(DeviceConfigItem("Threads",CPUInfo::GetCPUCount()*4));
	dc.AddConfigItem(DeviceConfigItem("Port", 8080));
}
