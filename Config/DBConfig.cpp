#include "DBConfig.h"

DBConfig::DBConfig() 
{
	dc = DeviceConfig("Database Config", "Database table size settings", NA, GENERIC);
	dc.AddConfigItem(DeviceConfigItem("EventTableSize", (long)524288000));
	dc.AddConfigItem(DeviceConfigItem("LogTableSize", (long)262144000));
}
