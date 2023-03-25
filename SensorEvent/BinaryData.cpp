#include "BinaryData.h"

BinaryData::BinaryData(std::string Name, std::string Data)
	: SensorDataBase(eSensorDataTypes::BINARY)
	, data(Data)
{
	name = Name;
}

cJSON *BinaryData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON_AddItemToObject(ret, "type", cJSON_CreateNumber(eSensorDataTypes::BINARY));
	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	std::string encoded = base64_encode(data);
	cJSON_AddItemToObject(ret, "data", cJSON_CreateString(data.c_str()));
	return ret;
}

BinaryData BinaryData::FromJSON(cJSON *json)
{
	std::string name, data;
	if (cJSON_HasObjectItem(json, "name"))
	{
		name = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "data"))
	{
		std::string tmp = cJSON_GetObjectItem(json, "data")->valuestring;
		data = base64_decode(tmp, true);
	}
	return BinaryData(name, data);
}

void BinaryData::StoreToDB(unsigned long eventID)
{
	DBBinaryData dbo;
	dbo.EventID = eventID;
	dbo.Data = data;
	dbo.Name = name;
	DB::GetInstance()->GetStorage()->insert(dbo);
}

