#include "JSONTools.h"

std::string JSONTools::JSONGetString(cJSON *obj, std::string name)
{
	if (cJSON_HasObjectItem(obj, name.c_str()))
		return cJSON_GetObjectItem(obj, name.c_str())->valuestring;
	return "";
}

int JSONTools::JSONGetInt(cJSON *obj, std::string name)
{
	if (cJSON_HasObjectItem(obj, name.c_str()))
		return cJSON_GetObjectItem(obj, name.c_str())->valueint;
	return -1;
}

float JSONTools::JSONGetFloat(cJSON *obj, std::string name)
{
	if (cJSON_HasObjectItem(obj, name.c_str()))
		return cJSON_GetObjectItem(obj, name.c_str())->valuedouble;
	return -1.0;
}

bool JSONTools::JSONGetBool(cJSON *obj, std::string name)
{
	if (cJSON_HasObjectItem(obj, name.c_str()))
		return (bool)cJSON_GetObjectItem(obj, name.c_str())->valueint;
	return false;
}

time_t JSONTools::JSONGetTime(cJSON *obj, std::string name)
{
	if (cJSON_HasObjectItem(obj, name.c_str()))
	{
		double v = cJSON_GetObjectItem(obj, name.c_str())->valuedouble;
		return ((time_t)v);
	}
	return 0;
}