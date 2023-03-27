#include "LogConfig.h"

LogConfig::LogConfig(bool useSTDIO,
	ELogLevel stdioLevel,
	bool useREST,
	ELogLevel restLevel,
	bool useDB,
	ELogLevel dbLevel,
	std::vector<std::string> restServers,
	uint restServerPort):
	useSTDIO(useSTDIO),
	stdioLevel(stdioLevel),
	useRESTLog(useREST),
	restLogLevel(restLevel),
	useDBLog(useDB),
	dbLogLevel(dbLevel),
	restServers(restServers),
	restServerPort(restServerPort)
{
}

LogConfig::LogConfig(DeviceConfig dc)
{
	ret.push_back(DeviceConfigItem("stdioLog", useSTDIO));
	ret.push_back(DeviceConfigItem("stdioLogLev", (long)stdioLevel));
	ret.push_back(DeviceConfigItem("dbLog", useDBLog));
	ret.push_back(DeviceConfigItem("dbLogLev", (long)dbLogLevel));
	ret.push_back(DeviceConfigItem("restLog", useRESTLog));
	ret.push_back(DeviceConfigItem("restLogLev", (long)restLogLevel));
	ret.push_back(DeviceConfigItem("restServerPort", (long)restServerPort));
	
	if (dc.HasConfigItem("stdioLog"))
		useSTDIO = dc.GetConfigItem("stdioLog").GetBoolVal();
	if (dc.HasConfigItem("stdioLogLev"))
		stdioLevel = (ELogLevel)dc.GetConfigItem("stdioLogLev").GetLongVal();
	if (dc.HasConfigItem("dbLog"))
		useDBLog = dc.GetConfigItem("dbLog").GetBoolVal();
	if (dc.HasConfigItem("dbLogLev"))
		dbLogLevel = (ELogLevel)dc.GetConfigItem("dbLogLevel").GetLongVal();
	if (dc.HasConfigItem("restLog"))
		useRESTLog = dc.GetConfigItem("restLog").GetBoolVal();
	if (dc.HasConfigItem("restLogLev"))
		restLogLevel = (ELogLevel)dc.GetConfigItem("restLogLev").GetLongVal();
	if (dc.HasConfigItem("restServerPort"))
		restServerPort = dc.GetConfigItem("restServerPort").GetLongVal();
	if (dc.HasConfigItem("restServers"))
	{
		std::string rss = dc.GetConfigItem("restServers").GetStringVal();
		std::istringstream iss(rss);
		std::string token;
		while (std::getline(iss, token, ','))
			restServers.push_back(token);		
	}
}

cJSON *LogConfig::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON_AddItemToObject(ret, "stdio", cJSON_CreateBool(useSTDIO));
	cJSON_AddItemToObject(ret, "stdioLevel", cJSON_CreateNumber((int)stdioLevel));
	cJSON_AddItemToObject(ret, "db", cJSON_CreateBool(useDBLog));
	cJSON_AddItemToObject(ret, "dbLevel", cJSON_CreateNumber((int)dbLogLevel));
	cJSON_AddItemToObject(ret, "rest", cJSON_CreateBool(useRESTLog));
	cJSON_AddItemToObject(ret, "restLevel", cJSON_CreateNumber((int)restLogLevel));
	cJSON_AddItemToObject(ret, "restServerPort", cJSON_CreateNumber(restServerPort));
	std::stringstream rs;
	for (int i = 0; i < restServers.size(); i++)
	{
		if (i == 0)
			rs << restServers[i];
		else
			rs << "," << restServers[i];
	}
	cJSON_AddItemToObject(ret, "restServers", cJSON_CreateString(rs.str().c_str()));
	
	return ret;	
}

LogConfig LogConfig::FromJSON(cJSON *json)
{
	bool stdio, db, rest;
	ELogLevel stdioLev, dbLev, restLevl;
	std::vector<std::string> restServers;
	int rsp = 8080;
	if (cJSON_HasObjectItem(json, "stdio"))
	{
		stdio = (bool)cJSON_GetObjectItem(json, "stdio")->valueint;
		if (cJSON_HasObjectItem(json, "stdioLevel"))
		{
			stdioLev = (ELogLevel)cJSON_GetObjectItem(json, "stdioLevel")->valueint;
		}
		else
		{
			stdioLev = ELogLevel::WARN;
		}				
	}
	else
	{
		stdio = false;
		stdioLev = ELogLevel::WARN;
	}
	if (cJSON_HasObjectItem(json, "db"))
	{
		db = (bool)cJSON_GetObjectItem(json, "db")->valueint;
		if (cJSON_HasObjectItem(json, "dbLevel"))
		{
			dbLev = (ELogLevel)cJSON_GetObjectItem(json, "dbLevel")->valueint;
		}
		else
		{
			dbLev = ELogLevel::WARN;
		}				
	}
	else
	{
		db = false;
		dbLev = ELogLevel::WARN;
	}
	if (cJSON_HasObjectItem(json, "rest"))
	{
		rest = (bool)cJSON_GetObjectItem(json, "rest")->valueint;
		if (cJSON_HasObjectItem(json, "restLevel"))
		{
			restLevl = (ELogLevel)cJSON_GetObjectItem(json, "restLevel")->valueint;
		}
		else
		{
			restLevl = ELogLevel::WARN;
		}				
		if (cJSON_HasObjectItem(json, "restServers"))
		{
			std::string rss = cJSON_GetObjectItem(json, "restServers")->valuestring;
			std::istringstream iss(rss);
			std::string token;
			while (std::getline(iss, token, ','))
				restServers.push_back(token);			
		}
		if (cJSON_HasObjectItem(json, "restServerPort"))
		{
			rsp = cJSON_GetObjectItem(json, "restServerPort")->valueint;
		}
	}
	else
	{
		rest = false;
		restLevl = ELogLevel::WARN;
	}
	
	return LogConfig(stdio, stdioLev, rest, restLevl, db, dbLev, restServers, rsp);
}

std::vector<DeviceConfigItem> LogConfig::ToDeviceConfig()
{
	std::vector<DeviceConfigItem> ret;
	ret.push_back(DeviceConfigItem("stdioLog", useSTDIO));
	ret.push_back(DeviceConfigItem("stdioLogLev", (long)stdioLevel));
	ret.push_back(DeviceConfigItem("dbLog", useDBLog));
	ret.push_back(DeviceConfigItem("dbLogLev", (long)dbLogLevel));
	ret.push_back(DeviceConfigItem("restLog", useRESTLog));
	ret.push_back(DeviceConfigItem("restLogLev", (long)restLogLevel));
	ret.push_back(DeviceConfigItem("restServerPort", (long)restServerPort));
	std::stringstream rs;
	for (int i = 0; i < restServers.size(); i++)
	{
		if (i == 0)
			rs << restServers[i];
		else
			rs << "," << restServers[i];
	}
	ret.push_back(DeviceConfigItem("restServers", rs.str()));	
	return ret;
}

void LogConfig::Update(DeviceConfig dc)
{
	if (dc.HasConfigItem("stdioLog"))
	{
		useSTDIO = dc.GetConfigItem("stdioLog").GetBoolVal();
		if (dc.HasConfigItem("stdioLogLev"))
		{
			stdioLevel = (ELogLevel)dc.GetConfigItem("stdioLogLev").GetLongVal();
		}
		else
		{
			stdioLevel = ELogLevel::WARN;
		}
	}
	else
	{
		useSTDIO = false;
		stdioLevel = ELogLevel::WARN;
	}
	if (dc.HasConfigItem("dbLog"))
	{
		useDBLog = dc.GetConfigItem("dbLog").GetBoolVal();
		if (dc.HasConfigItem("dbLogLev"))
		{
			dbLogLevel = (ELogLevel)dc.GetConfigItem("dbLogLev").GetLongVal();
		}
		else
		{
			dbLogLevel = ELogLevel::WARN;
		}
	}
	else
	{
		useDBLog = false;
		dbLogLevel = ELogLevel::WARN;
	}
	if (dc.HasConfigItem("restLog"))
	{
		useRESTLog = dc.GetConfigItem("restLog").GetBoolVal();
		if (dc.HasConfigItem("restLogLev"))
		{
			restLogLevel= (ELogLevel)dc.GetConfigItem("restLogLev").GetLongVal();
		}
		else
		{
			restLogLevel = ELogLevel::WARN;
		}
	}
	else
	{
		useRESTLog = false;
		restLogLevel = ELogLevel::WARN;
	}
	
	if (dc.HasConfigItem("restServers"))
	{
		restServers.clear();
		std::string rs = dc.GetConfigItem("restServers").GetStringVal();		
		std::istringstream iss(rs);
		std::string token;
		while (std::getline(iss, token, ','))
			restServers.push_back(token);	
	}
	if (dc.HasConfigItem("restServerPort"))
	{
		restServerPort = (uint)dc.GetConfigItem("restServerPort").GetLongVal();
	}
	
	Logger::GetInstance()->Update(
		useSTDIO,
		useDBLog,
		useRESTLog,
		stdioLevel,
		dbLogLevel,
		restLogLevel,
		restServerPort,
		restServers);	
}

