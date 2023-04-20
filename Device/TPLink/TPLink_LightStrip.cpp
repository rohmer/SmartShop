#include "TPLink_LightStrip.h"

TPLink_LightStrip::TPLink_LightStrip(cJSON *json, std::string ipAddr) :
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

bool TPLink_LightStrip::parseJSON(cJSON *j)
{
	deviceType = TPLink_Device::SmartLightStrip;
	if (!TPLink_Device::parseJSON(j))
	{
		return false;
	}
	
	length = JSONTools::JSONGetInt(j, "length");
	isDimmable = JSONTools::JSONGetBool(j, "is_dimmable");
	isColor= JSONTools::JSONGetBool(j, "is_color");
	isVariableColorTemp = JSONTools::JSONGetBool(j, "is_variable_color_temp");
	isFactory = JSONTools::JSONGetBool(j, "is_factory");
	activeMode = JSONTools::JSONGetString(j, "active_node");
	discoVer = JSONTools::JSONGetString(j, "disco_ver");
	
	if (cJSON_HasObjectItem(j, "lighting_effect_state"))
	{
		cJSON *les = cJSON_GetObjectItem(j, "lighting_effect_state");
		bool enable = JSONTools::JSONGetBool(les, "enable");
		std::string name = JSONTools::JSONGetString(les, "name");
		bool custom = JSONTools::JSONGetBool(les, "custom");
		std::string id = JSONTools::JSONGetString(les, "id");
		int brightness = JSONTools::JSONGetInt(les, "brightness");
		lightingEffectState = sLightingEffectState(enable, name, custom, id, brightness);	
	}
	
	if (cJSON_HasObjectItem(j, "light_state"))
	{
		cJSON *ls = cJSON_GetObjectItem(j, "light_state");
		lightOnOff = JSONTools::JSONGetBool(ls, "on_off");
		if (cJSON_HasObjectItem(ls, "dft_on_state"))
		{
			cJSON *dft = cJSON_GetObjectItem(ls, "dft_on_state");
			lightMode = JSONTools::JSONGetString(dft, "mode");
			hue = JSONTools::JSONGetInt(dft, "hue");
			saturation = JSONTools::JSONGetInt(dft, "saturation");
			colorTemp = JSONTools::JSONGetInt(dft, "color_temp");
			brightness = JSONTools::JSONGetInt(dft, "brightness");
		}
		
	}
	if (cJSON_HasObjectItem(j, "preferred_state"))
	{
		cJSON *arr = cJSON_GetObjectItem(j, "preferred_state");
		if (cJSON_IsArray(arr))
		{
			cJSON *itr;
			cJSON_ArrayForEach(itr, arr)
			{
				int index = JSONTools::JSONGetInt(itr, "index");
				int hue = JSONTools::JSONGetInt(itr, "hue");
				int saturation = JSONTools::JSONGetInt(itr, "saturation");
				int colorTemp = JSONTools::JSONGetInt(itr, "color_temp");
				int brightness = JSONTools::JSONGetInt(itr, "brightness");
				preferredStates.push_back(sPreferredState(
					index,
					hue,
					saturation,
					colorTemp,
					brightness)
					);
			}
		}
	}
	return true;
}