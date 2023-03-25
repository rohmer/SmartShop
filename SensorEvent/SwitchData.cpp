#include "SwitchData.h"

SwitchData::SwitchData(std::string Name, uint switchID, bool value) :
	SensorDataBase(eSensorDataTypes::SWITCH),
	id(switchID),
	val(value)
{
	name = Name;
}

void SwitchData::SetSwitchID(uint switchID)
{
	id = switchID;
}

void SwitchData::SetValue(bool value)
{
	val = value;
}

uint SwitchData::GetSwitchID()
{
	return id;
}

bool SwitchData::GetValue()
{
	return val;
}

cJSON *SwitchData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();

	cJSON *ctype = cJSON_CreateNumber(dataType);
	cJSON *cid = cJSON_CreateNumber(id);
	cJSON *cvalue = cJSON_CreateBool(val);
	
	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(ret, "type", ctype);
	cJSON_AddItemToObject(ret, "id", cid);
	cJSON_AddItemToObject(ret, "value", cvalue);
	return ret;
}

SwitchData SwitchData::FromJSON(cJSON *doc)
{
	unsigned int id;
	bool value = false;
	std::string name;
	if (cJSON_HasObjectItem(doc, "name"))
	{
		name = cJSON_GetObjectItem(doc, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(doc,"id"))
	{
		id = cJSON_GetObjectItem(doc,"id")->valueint;
	}
	if (cJSON_HasObjectItem(doc,"value"))
	{
		value = cJSON_GetObjectItem(doc, "value")->valueint;
	}
	
	return SwitchData(name, id, value);
}

void SwitchData::StoreToDB(unsigned long eventID)
{
	DBSwitchData dbo;
	dbo.EventID = eventID;
	dbo.SwitchID = id;
	dbo.Value = val;
	DB::GetInstance()->GetStorage()->insert(dbo);
}