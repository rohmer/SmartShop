#include "Caps.h"

Caps::Caps(bool hasClient, bool hasServer, bool hasUI)
	: client(hasClient)
	, server(hasServer)
	, ui(hasUI)
{
}

Caps Caps::FromJSON(cJSON *json)
{
	bool _client=false, _server=false, _ui=false;
	if (cJSON_HasObjectItem(json, "caps"))
	{
		cJSON *arr = cJSON_GetObjectItem(json, "caps");
		if (cJSON_IsArray(arr))
		{
			cJSON *c;
			cJSON_ArrayForEach(c, arr)
			{
				std::string cStr = c->valuestring;
				if (strcmp(cStr.c_str(), "CLIENT"))
				{
					_client = true;
				}
				else
				{
					if (strcmp(cStr.c_str(), "SERVER"))
					{
						_server = true;
					}
					else
					{
						if (strcmp(cStr.c_str(), "UI"))
						{
							_ui = true;
						}
						else
						{
							std::stringstream ss;
							ss << "Unknown capability defined: " << cStr;
							Logger::GetInstance()->LogW(ss.str());
						}
					}
				}
			}
		}
		else
		{
			Logger::GetInstance()->LogW("Caps in configuration is malformed, recreating");
			return Caps();
		}
		return Caps(_client, _server, _ui);
	}
	return Caps();
}

cJSON *Caps::ToJSON()
{
	cJSON *json=cJSON_CreateObject();
	cJSON *arr = cJSON_CreateArray();
	if (client)
		cJSON_AddItemToArray(arr, cJSON_CreateString("CLIENT"));
	if (server)
		cJSON_AddItemToArray(arr, cJSON_CreateString("SERVER"));
	if (ui)
		cJSON_AddItemToArray(arr, cJSON_CreateString("UI"));
	cJSON_AddItemToObject(json, "caps", arr);
	return json;		
}

std::vector<DeviceConfigItem> Caps::ToDeviceConfig()
{
	std::vector<DeviceConfigItem> ret;
	if (client)
		ret.push_back(DeviceConfigItem("CAP_CLIENT", true));
	else
		ret.push_back(DeviceConfigItem("CAP_CLIENT", false));
	if (server)
		ret.push_back(DeviceConfigItem("CAP_SERVER", true));
	else
		ret.push_back(DeviceConfigItem("CAP_SERVER", false));
	if (ui)
		ret.push_back(DeviceConfigItem("CAP_UI", true));
	else
		ret.push_back(DeviceConfigItem("CAP_UI", false));
	return ret;
}

Caps Caps::FromDeviceConfig(DeviceConfig dc)
{
	bool _server = false, _client = false, _ui = false;
	if (dc.HasConfigItem("CAP_CLIENT"))
		_client = dc.GetConfigItem("CAP_CLIENT").GetBoolVal();
	if (dc.HasConfigItem("CAP_SERVER"))
		_client = dc.GetConfigItem("CAP_SERVER").GetBoolVal();
	if (dc.HasConfigItem("CAP_UI"))
		_ui = dc.GetConfigItem("CAP_UI").GetBoolVal();
	return Caps(_client, _server, _ui);
}