#include "Config.h"
Config *Config::instance = NULL;

Config::Config() noexcept 
{
	LogConfig logConfig;
	configs.emplace(LogConfig::GetName(), logConfig.dc);
	DBConfig db;
	configs.emplace(DBConfig::GetName(), db.dc);
	TAConfig ta;
	configs.emplace(TAConfig::GetName(), ta.dc);
	RESTConfig rc;
	configs.emplace(RESTConfig::GetName(), rc.dc);
	CapabilitiesConfig cc;
	configs.emplace(CapabilitiesConfig::GetName(), cc.dc);
}

Config *Config::GetInstance()
{
	if (instance == NULL)
		instance = new Config();
	return instance;
}

void Config::AddDeviceConfig(DeviceConfig dc)
{
	configs.emplace(dc.GetName(), dc);
	SaveConfig();
}

bool Config::LoadConfig(std::string configFile)
{
	confFile = configFile;
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

	if (cJSON_HasObjectItem(json, "Capabilities"))
	{
		if (configs.find("Capabilties Config") == configs.end())
		{
			// This should never happen, but if it does..  Error
			Logger::GetInstance()->LogC("Could not find capabilties");
		}
		configs["Capabilties Config"]=DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "Capabilities"));
	}
	if (cJSON_HasObjectItem(json, "LogConfig"))
	{
		if (configs.find("Logger Configuration") == configs.end())
		{
			// This should never happen, but if it does..  Error
			Logger::GetInstance()->LogC("Could not find logger");
		}
		configs["Logger Configuration"] = DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "LogConfig"));
	}
	if (cJSON_HasObjectItem(json, "DBConfig"))
	{
		if (configs.find("Database Config") == configs.end())
		{
			// This should never happen, but if it does..  Error
			Logger::GetInstance()->LogC("Could not find DB config");
		}
		configs["Database Config"]= DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "DBConifg"));
	}
	if (cJSON_HasObjectItem(json, "RESTConfig"))
	{
		if (configs.find("REST Config") == configs.end())
		{
			// This should never happen, but if it does..  Error
			Logger::GetInstance()->LogC("Could not find REST Config");
		}
		configs["REST Config"] = DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "RESTConifg"));
	}
	if (cJSON_HasObjectItem(json, "TelemetryAgent"))
	{
		if (configs.find("Telemetry Agent") == configs.end())
		{
			// This should never happen, but if it does..  Error
			Logger::GetInstance()->LogC("Could not find Telemetry Agent");
		}
		configs["Telemetry Agent"] = DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "TelemetryAgent"));
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
	if (configFile.length() == 0)
		configFile = this->confFile;
	std::fstream out;
	out.open(configFile, std::ios::out);
	if (!out.is_open())
	{
		std::stringstream ss;
		ss << "Config file: " << configFile << " could not be written";
		Logger::GetInstance()->LogC(ss.str());
		return false;
	}
	
	cJSON *json = cJSON_CreateObject();;
	cJSON *cap = configs["Capabilities Config"].ToJSON();
	cJSON_AddItemToObject(json, "Capabilities", cap);
	cJSON_AddItemToObject(json,
		"Capabilities",
		configs["Capabilties Config"].ToJSON());
	cJSON_AddItemToObject(json, "DBConfig", 
		configs["Database Config"].ToJSON());
	cJSON_AddItemToObject(json, "LogConfig", 
		configs["Logger Configuration"].ToJSON());
	cJSON_AddItemToObject(json, "RESTConfig", 
		configs["REST Config"].ToJSON());
	cJSON_AddItemToObject(json,
		"TelemetryAgent",
		configs["Telemetry Agent"].ToJSON());
	std::string jstr = JSON::Print(json);
	
	out << jstr;
	out.close();
	try
	{
		delete(json);
	}
	catch (const std::exception&)
	{		
	}
	return true;
}

std::vector<std::string> Config::GetRestLogServers()
{
	std::string rs = configs["REST Config"].GetConfigItem("RESTServers").GetStringVal();
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
	std::vector<std::string> ret;
	while ((pos = rs.find(delimiter)) != std::string::npos)
	{
		token = rs.substr(0, pos);
		ret.push_back(token);
		rs.erase(0, pos + delimiter.length());
	}
	return ret;
}

void Config::AddRestLogServer(std::string server)
{
	std::string currentServers = configs["REST Config"].GetConfigItem("RESTServers").GetStringVal();
	if (currentServers.length() == 0)
		currentServers = server;
	else
	{
		std::stringstream ss;
		ss << currentServers << "," << server;
		currentServers = ss.str();
	}
	configs["REST Config"].SetConfigItem(DeviceConfigItem("RESTServers", currentServers));
	SaveConfig();
}

void Config::ClearRestLogServers()
{
	configs["REST Config"].SetConfigItem(DeviceConfigItem("RESTServers", ""));
	SaveConfig();
}

void Config::RemoveRestLogServer(std::string server)
{
	std::string rs = configs["REST Config"].GetConfigItem("RESTServers").GetStringVal();
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
	std::vector<std::string> ret;
	while ((pos = rs.find(delimiter)) != std::string::npos)
	{
		token = rs.substr(0, pos);
		if (std::strcmp(token.c_str(), server.c_str()) != 0)
			ret.push_back(server);
		rs.erase(0, pos + delimiter.length());
	}
	SaveConfig();
}

Config::EConfigSetResult Config::SetConfigVariable(std::string ConfigName, 
	std::string VariableName, 
	std::string Value)
{
	if (configs.find(ConfigName) == configs.end())
	{
		std::stringstream ss;
		ss << "DeviceConfig: " << ConfigName << " does not exist";
		Logger::GetInstance()->LogC(ss.str());
		return Config::eCONFIGDOESNOTEXIST;
	}
	DeviceConfig dc = configs[ConfigName];
	if (!dc.HasConfigItem(VariableName))
	{
		std::stringstream ss;
		ss << "DeviceConfig: " << ConfigName << " does not have variable: " << VariableName;
		Logger::GetInstance()->LogC(ss.str());
		return Config::eVARIABLEDOESNOTEXIST;
	}
	DeviceConfigItem dci = dc.GetConfigItem(VariableName);
	if (dci.IsReadOnly())
	{
		std::stringstream ss;
		ss << "DeviceConfig: " << ConfigName << " variable: " << VariableName << " is read-only";
		Logger::GetInstance()->LogC(ss.str());
		return Config::eVARIABLEDOESNOTEXIST;
	}
	
	switch (dci.GetDataType())
	{
	case eConfigDataType::C_BOOL:
		{
			if (std::strcmp(Value.c_str(), "1") == 0)
			{
				dci.SetValue(true);
			}
			else
			{
				dci.SetValue(false);
			}
			configs[ConfigName].SetConfigItem(dci);
			break;
		}
	case eConfigDataType::C_FLOAT:
		{
			float v = std::atof(Value.c_str());
			dci.SetValue(v);
			configs[ConfigName].SetConfigItem(dci);
			break;
		}
	case eConfigDataType::C_LONG:
		{
			long l = std::atol(Value.c_str());
			dci.SetValue(l);
			configs[ConfigName].SetConfigItem(dci);
			break;
		}
	case eConfigDataType::C_STR:
		{
			dci.SetValue(Value);
			configs[ConfigName].SetConfigItem(dci);
			break;
		}
	}
	return Config::eSUCCESS;
}