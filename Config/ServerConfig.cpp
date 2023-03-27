#include "ServerConfig.h"

ServerConfig::ServerConfig(
	uint serverPort,
	uint serverThreads)
	: serverPort(serverPort)
	, serverThreads(serverThreads)
{
}

ServerConfig ServerConfig::FromJSON(cJSON *json)
{
	uint threads=8, port=8080;
	if (cJSON_HasObjectItem(json, "serverThreads"))
	{
		threads = cJSON_GetObjectItem(json, "serverThreads")->valueint;
	}
	if (cJSON_HasObjectItem(json, "serverPort"))
	{
		port = cJSON_GetObjectItem(json, "serverPort")->valueint;
	}
	return ServerConfig(threads, port);
}

cJSON *ServerConfig::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "serverThreads", cJSON_CreateNumber(serverThreads));
	cJSON_AddItemToObject(json, "serverPort", cJSON_CreateNumber(serverPort));
	return json;
}

std::vector<DeviceConfigItem> ServerConfig::ToDeviceConfig()
{
	std::vector<DeviceConfigItem> ret;
	ret.push_back(DeviceConfigItem("serverThreads", (long)serverThreads));
	ret.push_back(DeviceConfigItem("serverPort", (long)serverPort));
	return ret;
}

void ServerConfig::Update(DeviceConfig dc)
{
	bool changed = false;
	if (dc.HasConfigItem("serverThreads"))
	{
		if (dc.GetConfigItem("serverThreads").GetLongVal() != serverThreads)
		{
			serverThreads = dc.GetConfigItem("serverThreads").GetLongVal();
			changed = true;
		}
	}
	if (dc.HasConfigItem("serverPort"))
	{
		if (dc.GetConfigItem("serverPort").GetLongVal() != serverPort)
		{
			serverPort = dc.GetConfigItem("serverPort").GetLongVal();
			changed = true;
		}
	}
	if (changed)
	{
		RESTServer *rs = RESTServer::GetInstance();
		rs->Update(serverPort, serverThreads);
	}
}