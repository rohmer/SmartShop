#include "Config.h"

Config::Config()
{
}

bool Config::LoadConfig(std::string configFile)
{
	if (!std::filesystem::exists(configFile))
	{
		std::stringstream ss;
		ss << "Config file: " << configFile << " does not exist";
		Logger::GetInstance()->LogI(ss.str());
		return false;
	}
	
	std::stringstream ss;
	std::fstream fs;
	fs.open(configFile, std::ios::in);
	if (!fs.is_open())
	{
		std::stringstream ss;
		ss << "Config file: " << configFile << " could not be read";
		Logger::GetInstance()->LogI(ss.str());
		return false;
	}
	
	std::string line;
	while (getline(fs, line))
	{
		ss << line << "\n";
	}
	fs.close();
	
	cJSON *json;
	try
	{
		json = cJSON_Parse(ss.str().c_str());
	}
	catch (std::exception)
	{
		std::stringstream ss;
		ss << "Config file: " << configFile << " could not be parsed";
		Logger::GetInstance()->LogI(ss.str());
		return false;
	}
	
	if (cJSON_HasObjectItem(json, "db"))
	{
		dbConfig = DBConfig::FromJSON(cJSON_GetObjectItem(json, "db"));
	}
	if (cJSON_HasObjectItem(json, "log"))
	{
		logConfig = LogConfig::FromJSON(cJSON_GetObjectItem(json, "log"));
	}
	if (cJSON_HasObjectItem(json, "server"))
	{
		serverConfig = ServerConfig::FromJSON(cJSON_GetObjectItem(json, "server"));
	}
	if (cJSON_HasObjectItem(json, "caps"))
	{
		caps = Caps::FromJSON(cJSON_GetObjectItem(json, "caps"));
	}
	if (cJSON_HasObjectItem(json, "tAgent"))
	{
		taConfig = TelemetryAgentConfig::FromJSON(cJSON_GetObjectItem(json, "tAgent"));
	}
	try
	{
		cJSON_Delete(json);
	}
	catch (const std::exception&)
	{
	}
	return true;
}

bool Config::SaveConfig(std::string configFile)
{
	std::fstream out;
	out.open(configFile, std::ios::out);
	if (!out.is_open())
	{
		std::stringstream ss;
		ss << "Config file: " << configFile << " could not be written";
		Logger::GetInstance()->LogC(ss.str());
		return false;
	}
	cJSON *json;
	cJSON_AddItemToObject(json, "db", dbConfig.ToJSON());
	cJSON_AddItemToObject(json, "log", logConfig.ToJSON());
	cJSON_AddItemToObject(json, "server", serverConfig.ToJSON());
	cJSON_AddItemToObject(json, "caps", caps.ToJSON());
	cJSON_AddItemToObject(json, "tAgent", taConfig.ToJSON());
	std::stringstream ss;
	ss << JSON::Print(json);
	out << ss.str();
	out.close();
	std::stringstream ls;
	ls << "Wrote config file to: " << configFile;
	Logger::GetInstance()->LogI(ls.str());
}

DeviceConfig Config::GetLogConfig()
{
	DeviceConfig dc("Log Settings", "Log setttings for node",NA,GENERIC);
	std::vector<DeviceConfigItem> items = logConfig.ToDeviceConfig();
	for (int i = 0; i<items.size(); i++)
		dc.AddConfigItem(items[i]);
	return dc;
}
DeviceConfig Config::GetServerConfig()
{
	DeviceConfig dc("Server Settings", "Server setttings for node",NA,GENERIC);
	std::vector<DeviceConfigItem> items = serverConfig.ToDeviceConfig();
	for (int i = 0; i < items.size(); i++)
		dc.AddConfigItem(items[i]);
	return dc;

}

DeviceConfig Config::GetDBConfig()
{
	DeviceConfig dc("DB Settings", "Database setttings for node", NA, GENERIC);
	std::vector<DeviceConfigItem> items = dbConfig.ToDeviceConfig();
	for (int i = 0; i < items.size(); i++)
		dc.AddConfigItem(items[i]);
	return dc;

}
DeviceConfig Config::GetCapsConfig()
{
	DeviceConfig dc("Capability Settings", "Capability setttings for node", NA, GENERIC);
	std::vector<DeviceConfigItem> items = caps.ToDeviceConfig();
	for (int i = 0; i < items.size(); i++)
		dc.AddConfigItem(items[i]);
	return dc;

}
DeviceConfig Config::GetTelemetryAgentConfig()
{
	DeviceConfig dc("Telemetry Agent Settings", "Telemetry Agent setttings for node", NA, GENERIC);
	std::vector<DeviceConfigItem> items = taConfig.ToDeviceConfig();
	for (int i = 0; i < items.size(); i++)
		dc.AddConfigItem(items[i]);
	return dc;

}