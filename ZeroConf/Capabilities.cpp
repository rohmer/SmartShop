#include "Capabilities.h"

Capabilities::Capabilities()
{
}

Capabilities::Capabilities(DeviceConfig dc)
{
	Update(dc);
}

void Capabilities::Update(DeviceConfig dc)
{
	capabilities.clear();
	if (dc.HasConfigItem("UI"))
	{
		if (dc.GetConfigItem("UI").GetBoolVal())
			capabilities.push_back(eCaps::CAP_UI);
	}
	if (dc.HasConfigItem("CLIENT"))
	{
		if (dc.GetConfigItem("CLIENT").GetBoolVal())
			capabilities.push_back(eCaps::CAP_CLIENT);
	}
	if (dc.HasConfigItem("SERVER"))
	{
		if (dc.GetConfigItem("SERVER").GetBoolVal())
			capabilities.push_back(eCaps::CAP_SERVER);
	}
}
void Capabilities::AddCap(eCaps capabilitiy)
{
	bool exists = false;
	for (std::vector<eCaps>::iterator it = capabilities.begin(); it != capabilities.end(); ++it)
	{
		if (*it == capabilitiy)
		{
			exists = true;
			break;
		}
	}
	if (exists)
		return;
	capabilities.push_back(capabilitiy);
}

bool Capabilities::HasCap(eCaps capabilitiy)
{
	for (std::vector<eCaps>::iterator it = capabilities.begin(); it != capabilities.end(); ++it)
	{
		if (*it == capabilitiy)
		{
			return true;
		}
	}
	return false;
}

cJSON *Capabilities::ToJSON()
{
	cJSON *doc = cJSON_CreateObject();
	cJSON *capArray = cJSON_CreateArray();
	for (std::vector<eCaps>::iterator it = capabilities.begin(); it != capabilities.end(); ++it)
	{
		cJSON_AddItemToArray(capArray, cJSON_CreateNumber(*it));
	}
	cJSON_AddItemToObject(doc, "caps", capArray);
	cJSON_AddItemToObject(doc, "hostname", cJSON_CreateString(CPUInfo::GetHostname().c_str()));
	cJSON_AddItemToObject(doc, "hostID", cJSON_CreateString(CPUInfo::GetCPUID().c_str()));
	cJSON_AddItemToObject(doc, "comPort", cJSON_CreateNumber(comPort));
	return doc;
}

Capabilities Capabilities::FromJSON(cJSON *json)
{
	if (!cJSON_HasObjectItem(json, "caps"))
	{
		return Capabilities();
	}
	
	Capabilities caps;
	
	cJSON *capArray = cJSON_GetObjectItem(json, "caps");
	cJSON *cap;
	cJSON_ArrayForEach(cap, capArray)
	{
		caps.AddCap((eCaps)cJSON_GetNumberValue(cap));
	}
	std::string hn, hid;
	if (cJSON_HasObjectItem(json, "hostname"))
	{
		hn = cJSON_GetObjectItem(json, "hostname")->valuestring;
		caps.SetHostname(hn);
	}
	if (cJSON_HasObjectItem(json, "hostID"))
	{
		hid = cJSON_GetObjectItem(json, "hostID")->valuestring;
		caps.SetHostID(hid);
	}
	return caps;
}

