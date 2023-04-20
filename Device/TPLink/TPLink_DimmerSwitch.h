#pragma once

#include <sstream>
#include <string>

#include "TPLink_Device.h"
#include <cJSON.h>
#include "JSONTools.h"

class TPLink_DimmerSwitch : public TPLink_Device
{
public:
	TPLink_DimmerSwitch(cJSON* json, std::string ipAddr);

	bool parseJSON(cJSON* json);

	struct sDimmableSwitchObject
	{
	public:

		sDimmableSwitchObject(std::string ID, std::string Alias, bool State, int brightness, time_t OnTime)
			: id(ID)
			, state(State)
			, alias(Alias)
			, onTime(OnTime)
			, brightness(brightness)
		{
		}
		std::string id, alias;
		bool state;
		time_t onTime;
		int brightness;
		// TODO Figure out next action
	};
	struct sPreferredStateObject
	{
		sPreferredStateObject(int index, int brightness) :
			index(index),
			brightness(brightness)
		{}
		int index, brightness;
	};

private:
	std::string feature, activeMode;
	bool relayState, led_off;
	time_t onTime;
	int brightness;
	std::vector<sDimmableSwitchObject> switchObjects; // For multiswitch devices;
	std::vector<sPreferredStateObject> preferredStates;
};
