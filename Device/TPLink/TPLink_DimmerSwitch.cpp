#include "TPLink_DimmerSwitch.h"


TPLink_DimmerSwitch::TPLink_DimmerSwitch(cJSON *json, std::string ipAddr) :
	TPLink_Device(ipAddr)
{
	deviceType = TPLink_Device::SmartSwitchDimmer;
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

bool TPLink_DimmerSwitch::parseJSON(cJSON *j)
{
	if (!TPLink_Device::parseJSON(j))
	{
		return false;
	}
	feature = JSONTools::JSONGetString(j, "feature");
	activeMode = JSONTools::JSONGetString(j, "active_mode");
	relayState = JSONTools::JSONGetBool(j, "relay_stat");
	led_off = JSONTools::JSONGetBool(j, "led_off");
	onTime = JSONTools::JSONGetTime(j, "on_time");
	brightness = JSONTools::JSONGetInt(j, "brightness");
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
				int brightness = JSONTools::JSONGetInt(iter, "brightness");
				switchObjects.push_back(sDimmableSwitchObject(id, alias, state, brightness, onTime));
			}
		}
	}
	else
	{
		switchObjects.push_back(sDimmableSwitchObject("00", alias, relayState, brightness, onTime));	
	}
	
	if (cJSON_HasObjectItem(j, "preferred_state"))
	{
		cJSON *arr = cJSON_GetObjectItem(j, "preferred_state");
		if (cJSON_IsArray(arr))
		{
			cJSON *itr;
			cJSON_ArrayForEach(itr, arr)
			{
				int bright = JSONTools::JSONGetInt(itr, "brightness");
				int index = JSONTools::JSONGetInt(itr, "index");
				sPreferredStateObject spso(index, bright);
				preferredStates.push_back(spso);
			}
			
		}
	}
	return true;
}