#include "DBConfig.h"

DBConfig::DBConfig(ulong maxLogSize, ulong maxSensorSize)
	: maxLogSize(maxLogSize)
	, maxSensorSize(maxSensorSize)
{
}

DBConfig DBConfig::FromJSON(cJSON *json)
{
	ulong maxLog = 52428800, maxSensor = 524288000;
	if (cJSON_HasObjectItem(json, "maxLog"))
		maxLog = cJSON_GetObjectItem(json, "maxLog")->valueint;
	if (cJSON_HasObjectItem(json, "maxSensor"))
		maxSensor = cJSON_GetObjectItem(json, "maxSensor")->valueint;
	return DBConfig(maxLog, maxSensor);
}

cJSON *DBConfig::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "maxLog", cJSON_CreateNumber(maxLogSize));
	cJSON_AddItemToObject(json, "maxSensor", cJSON_CreateNumber(maxSensorSize));
	return json;
}

std::vector<DeviceConfigItem> DBConfig::ToDeviceConfig()
{
	std::vector<DeviceConfigItem> ret;
	ret.push_back(DeviceConfigItem("maxLog", (long)maxLogSize));
	ret.push_back(DeviceConfigItem("maxSensor", (long)maxSensorSize));
	return ret;
}

void DBConfig::Update(DeviceConfig dc)
{
	if (dc.HasConfigItem("maxLog"))
		maxLogSize = dc.GetConfigItem("maxLog").GetLongVal();
	if (dc.HasConfigItem("maxSensor"))
		maxSensorSize = dc.GetConfigItem("maxSensor").GetLongVal();
}