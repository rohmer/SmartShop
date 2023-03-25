#include "StringData.h"

StringData::StringData(std::string Name, std::string Value)
	: SensorDataBase(eSensorDataTypes::STRING)
	, value(Value)
{
	name = Name;
}

cJSON *StringData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON_AddItemToObject(ret, "type", cJSON_CreateNumber(eSensorDataTypes::STRING));
	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(ret, "value", cJSON_CreateString(value.c_str()));
	return ret;
}

StringData StringData::FromJSON(cJSON *json)
{
	std::string name = "";
	std::string value = "";
	
	if (cJSON_HasObjectItem(json, "name"))
	{
		name = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "value"))
	{
		value = cJSON_GetObjectItem(json, "value")->valuestring;
	}
	return StringData(name, value);
}

void StringData::StoreToDB(unsigned long eventID)
{
	DBStringData dbo;
	dbo.EventID = eventID;
	dbo.Name = name;
	dbo.Value = value;
	DB::GetInstance()->GetStorage()->insert(dbo);
}