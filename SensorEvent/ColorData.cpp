#include "ColorData.h"

ColorData::ColorData(std::string Name, float Red, float Green, float Blue, float Alpha)
	: SensorDataBase(eSensorDataTypes::COLOR)
	, r(Red)
	, g(Green)
	, b(Blue)
	, a(Alpha)
{
	name = Name;
}

cJSON *ColorData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON *red = cJSON_CreateNumber(r);
	cJSON *green = cJSON_CreateNumber(g);
	cJSON *blue = cJSON_CreateNumber(b);
	cJSON *alpha = cJSON_CreateNumber(a);

	cJSON_AddItemToObject(ret, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(ret, "r", red);
	cJSON_AddItemToObject(ret, "g", green);
	cJSON_AddItemToObject(ret, "b", blue);
	cJSON_AddItemToObject(ret, "a", alpha);
	cJSON_AddItemToObject(ret, "type", cJSON_CreateNumber(eSensorDataTypes::COLOR));
	return ret;
}

ColorData ColorData::FromJSON(cJSON *json)
{
	float red=0, green=0, blue=0, alpha=0;
	std::string name;
	if (cJSON_HasObjectItem(json, "name"))
	{
		name = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "r"))
	{
		red = cJSON_GetObjectItem(json, "r")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "g"))
	{
		green = cJSON_GetObjectItem(json, "g")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "b"))
	{
		blue = cJSON_GetObjectItem(json, "b")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "a"))
	{
		alpha = cJSON_GetObjectItem(json, "a")->valuedouble;
	}
	return ColorData(name, red, green, blue, alpha);
}

void ColorData::StoreToDB(unsigned long eventID)
{
	DBColorData dbo;
	dbo.Alpha = a;
	dbo.Blue = b;
	dbo.EventID = eventID;
	dbo.Green = g;
	dbo.Red = r;
	DB::GetInstance()->GetStorage()->insert(dbo);
}