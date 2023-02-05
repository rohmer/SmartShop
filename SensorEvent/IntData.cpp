#include "IntData.h"

IntData::IntData(std::string Name, long Value)
	: SensorDataBase(eSensorDataTypes::INTEGER)
	, name(Name)
	, value(Value)
{
}

cJSON *IntData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON_AddItemToObject(ret, "type", cJSON_CreateNumber(eSensorDataTypes::INTEGER));
	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(ret, "value", cJSON_CreateNumber(value));
	return ret;
}

IntData IntData::FromJSON(cJSON *json)
{
	std::string name = "";
	int value = 0;
	
	if (cJSON_HasObjectItem(json, "name"))
	{
		name = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "value"))
	{
		value = cJSON_GetObjectItem(json, "value")->valueint;
	}
	return IntData(name, value);
}

void IntData::StoreToDB(unsigned long eventID)
{
	DBIntData dbo;
	dbo.EventID = eventID;
	dbo.Name = name;
	dbo.Value = value;
	DB::GetInstance()->GetStorage()->insert(dbo);
}