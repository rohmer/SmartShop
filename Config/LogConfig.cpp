#include "LogConfig.h"

LogConfig::LogConfig()
{
	dc = DeviceConfig(
		"Logger Configuration",
		"Configuration for Logger on this device",
		eDeviceBus::NA,
		eDeviceType::GENERIC);
#ifdef DEBUG
	dc.AddConfigItem(DeviceConfigItem("STDIO", true));
	dc.AddConfigItem(DeviceConfigItem("STDIOLevel", (int)ELogLevel::INFO));
#else
	dc.AddConfigItem(DeviceConfigItem("STDIO", false));
	dc.AddConfigItem(DeviceConfigItem("STDIOLevel", (int)ELogLevel::WARN));
#endif
	dc.AddConfigItem(DeviceConfigItem("DB", false));
#ifdef DEBUG
	dc.AddConfigItem(DeviceConfigItem("DBLevel", (int)ELogLevel::INFO));
#else
	dc.AddConfigItem(DeviceConfigItem("DBLevel", (int)ELogLevel::WARN));
#endif
	dc.AddConfigItem(DeviceConfigItem("RESTLog", false));
#ifdef DEBUG
	dc.AddConfigItem(DeviceConfigItem("RESTLevel", (int)ELogLevel::INFO));				  
#else
	dc.AddConfigItem(DeviceConfigItem("RESTLevel", (int)ELogLevel::WARN));
#endif
	dc.AddConfigItem(DeviceConfigItem("RESTPort", 8080));
	dc.AddConfigItem(DeviceConfigItem("RESTServers", ""));
}
