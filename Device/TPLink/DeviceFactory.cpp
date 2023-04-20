#include "DeviceFactory.h"

std::shared_ptr<TPLink_Device> DeviceFactory::CreateDevice(cJSON *j, std::string ipAddr)
{
	if (cJSON_HasObjectItem(j, "system"))
	{
		j = cJSON_GetObjectItem(j, "system");
	}
	if (cJSON_HasObjectItem(j, "get_sysinfo"))
	{
		j = cJSON_GetObjectItem(j, "get_sysinfo");
	}
	std::string dt = JSONTools::JSONGetString(j, "mic_type");
	if (dt.length() == 0)
	{
		dt = JSONTools::JSONGetString(j, "type");
		if (dt.length() == 0)
			return NULL;
	}
	if (strcmp(dt.c_str(), "IOT.SMARTPLUGSWITCH")==0)
	{
		bool dimmer = false;
		std::string model = JSONTools::JSONGetString(j, "model");
		if (strcmp(model.substr(0,5).c_str(), "HS220") == 0)
			dimmer = true;
		if (strcmp(model.substr(0, 5).c_str(), "KS220") == 0)
			dimmer = true;
		if (strcmp(model.substr(0, 5).c_str(), "KS230") == 0)
			dimmer = true;
		if (dimmer)
		{
			std::shared_ptr<TPLink_DimmerSwitch> sw =
				std::make_shared<TPLink_DimmerSwitch>(TPLink_DimmerSwitch(j,ipAddr));
			return (sw);
		}
		else
		{
			std::shared_ptr<TPLink_Switch> sw = std::make_shared<TPLink_Switch>(TPLink_Switch(j, ipAddr));
	
			return (sw);
		};
	}
	if (strcmp(dt.c_str(), "IOT.SMARTBULB")==0)
	{
		bool lightStrip = false;
		std::string model = JSONTools::JSONGetString(j, "model");
		if (strcmp(model.substr(0, 5).c_str(), "KL430") == 0)
			lightStrip = true;
		if (lightStrip)
		{
			std::shared_ptr<TPLink_LightStrip> sw = std::make_shared<TPLink_LightStrip>(TPLink_LightStrip(j, ipAddr));
				
			return (sw);
		}
		
		std::shared_ptr<TPLink_Bulb> sw = std::make_shared<TPLink_Bulb>(TPLink_Bulb(j,ipAddr));
		return (sw);
	}
}