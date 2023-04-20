#include "TPLink_Switch.h"

TPLink_Switch::TPLink_Switch(cJSON *json, std::string ipAddr) :
	TPLink_Device(ipAddr)
{
	if (cJSON_HasObjectItem(json, "system"))
	{
		json = cJSON_GetObjectItem(json, "system");
	}
	if (cJSON_HasObjectItem(json, "get_sysinfo"))
	{
		json = cJSON_GetObjectItem(json, "get_sysinfo");
	}
	
	if (!parseJSON(json))
	{
		std::stringstream ss;
		ss << "Failed to parse JSON for device: " << JSON::Print(json);
		log->LogC(ss.str());
		isValid = false;
	}
	else
		isValid = true;
}

bool TPLink_Switch::parseJSON(cJSON *j)
{
	deviceType = TPLink_Device::SmartSwitch;
	if (!TPLink_Device::parseJSON(j))
	{
		return false;
	}
	feature = JSONTools::JSONGetString(j, "feature");
	activeMode = JSONTools::JSONGetString(j, "active_mode");
	relayState = JSONTools::JSONGetBool(j, "relay_stat");
	led_off = JSONTools::JSONGetBool(j, "led_off");
	onTime = JSONTools::JSONGetTime(j, "on_time");
	
	if (cJSON_HasObjectItem(j, "children"))
	{
		cJSON *arr = cJSON_GetObjectItem(j, "children");
		if (cJSON_IsArray(arr))
		{
			cJSON *iter;
			cJSON_ArrayForEach(iter, arr)
			{
				std::string id, alias;
				time_t onTime;
				bool state;
				onTime = JSONTools::JSONGetTime(iter, "on_time");
				id = JSONTools::JSONGetString(iter, "id");
				alias = JSONTools::JSONGetString(iter, "alias");
				state = JSONTools::JSONGetBool(iter, "state");
				switchObjects.push_back(sSwitchObject(id, alias, state, onTime));
			}
		}
	}
	else
	{
		switchObjects.push_back(sSwitchObject("00", alias, relayState, onTime));	
	}
	
	return true;
}