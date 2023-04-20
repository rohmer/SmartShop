#pragma once

#include <sstream>
#include <string>

#include "TPLink_Device.h"
#include <cJSON.h>
#include "JSONTools.h"

class TPLink_LightStrip : public TPLink_Device
{
public:
	TPLink_LightStrip(cJSON* json,std::string ipAddr);

	bool parseJSON(cJSON* json);

	struct sLightingEffectState
	{
	public:
		sLightingEffectState()
		{
		}

		sLightingEffectState(bool enable,
			std::string name,
			bool custom,
			std::string id,
			int brightness) :
			enable(enable),
			name(name),
			custom(custom),
			id(id),
			brightness(brightness)
		{			
		}

		bool enable;
		std::string name, id;
		bool custom;
		int brightness, index;
	};
	
	struct sPreferredState
	{
	public:
		sPreferredState()
		{}
		sPreferredState(int index,
			int hue,
			int saturation,
			int color_temp,
			int brightness) :
			index(index),
			hue(hue),
			saturation(saturation),
			color_temp(color_temp),
			brightness(brightness)
		{
		}

		int index, hue, saturation, color_temp, brightness;

	};
private:
	std::string  activeMode;
	int brightness, length;
	bool isDimmable, isColor, isVariableColorTemp, isFactory;
	std::string discoVer;
	sLightingEffectState lightingEffectState;
	std::vector<sPreferredState> preferredStates;

	bool lightOnOff;
	int hue, saturation, colorTemp;
	std::string lightMode;
};
