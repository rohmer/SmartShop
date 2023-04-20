#pragma once

#include <sstream>
#include <string>

#include "TPLink_Device.h"
#include <cJSON.h>
#include "JSONTools.h"

class TPLink_Switch : public TPLink_Device
{
public:
	TPLink_Switch(cJSON* json, std::string ipAddr);

	bool parseJSON(cJSON* json);

	struct sSwitchObject
	{
	public:
		
		sSwitchObject(std::string ID, std::string Alias, bool State, time_t OnTime)
			: id(ID)
			, state(State)
			, alias(Alias)
			, onTime(OnTime)
		{
		}
		
		std::string id, alias;
		bool state;
		time_t onTime;
		// TODO Figure out next action
	};
private:
	std::string feature, activeMode;
	bool relayState, led_off;
	time_t onTime;
	std::vector<sSwitchObject> switchObjects; // For multiswitch devices;
	
};
