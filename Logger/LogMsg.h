#pragma once

#include <time.h>
#include <string>

#include "cJSON.h"
#include "LogLevel.h"

class LogMsg
{
public:
	unsigned long ID;
	std::string Host;
	int Severity;
	std::string Message;
	time_t Timestamp;
	std::string HostID;
	
	cJSON *ToJSON()
	{
		cJSON *j;
		cJSON_AddItemToObject(j, "host", cJSON_CreateString(Host.c_str()));
		cJSON_AddItemToObject(j, "msg", cJSON_CreateString(Message.c_str()));
		cJSON_AddItemToObject(j, "sev", cJSON_CreateNumber(Severity));
		cJSON_AddItemToObject(j, "time", cJSON_CreateNumber(Timestamp));
		cJSON_AddItemToObject(j, "hostID", cJSON_CreateString(HostID.c_str()));
		return j;
	}
	
	static LogMsg FromJSON(cJSON *j)
	{
		LogMsg lm;
	
		if (cJSON_HasObjectItem(j, "host"))
			lm.Host = cJSON_GetObjectItem(j, "host")->valuestring;
		if (cJSON_HasObjectItem(j, "msg"))
			lm.Message = cJSON_GetObjectItem(j, "msg")->valuestring;
		if (cJSON_HasObjectItem(j, "sev"))
			lm.Severity = cJSON_GetObjectItem(j, "sev")->valueint;
		if (cJSON_HasObjectItem(j, "time"))
			lm.Timestamp = cJSON_GetObjectItem(j, "time")->valueint;
		else
			lm.Timestamp = time(NULL);
		if (cJSON_HasObjectItem(j, "hostID"))
			lm.HostID = cJSON_GetObjectItem(j, "hostID")->valuestring;		
		return lm;
	}
	
};