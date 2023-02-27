#include "FloatData.h"

FloatData::FloatData(std::string Name, float Value)
	: SensorDataBase(eSensorDataTypes::FLOAT)
	, name(Name)
	, value(Value)
{
}

cJSON *FloatData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON_AddItemToObject(ret, "type", cJSON_CreateNumber(eSensorDataTypes::FLOAT));
	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(ret, "value", cJSON_CreateNumber(value));
	return ret;
}

FloatData FloatData::FromJSON(cJSON *json)
{
	std::string name = "";
	float value = 0;
	
	if (cJSON_HasObjectItem(json, "name"))
	{
		name = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "value"))
	{
		value = (float)cJSON_GetObjectItem(json, "value")->valuedouble;
	}
	return FloatData(name, value);
}

void FloatData::StoreToDB(unsigned long eventID)
{
	DBFloatData dbo;
	dbo.EventID = eventID;
	dbo.Name = name;
	dbo.Value = value;
	DB::GetInstance()->GetStorage()->insert(dbo);
}