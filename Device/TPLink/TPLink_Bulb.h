#pragma once

#include <sstream>
#include <string>

#include "TPLink_Device.h"
#include <cJSON.h>
#include "JSONTools.h"

class TPLink_Bulb : public TPLink_Device
{
public:
	TPLink_Bulb(cJSON* json, std::string ipAddr);

	bool parseJSON(cJSON* json);

	struct sLightState
	{
	public:
		sLightState()
		{}
		sLightState(
			bool isOn,
			std::string mode,
			int hue,
			int saturation,
			int colorTemp,
			int brightness) :
			isOn(isOn),
			mode(mode),
			hue(hue),
			saturation(saturation),
			colorTemp(colorTemp),
			brightness(brightness)
		{}
		bool isOn;
		std::string mode;
		int hue, saturation, colorTemp, brightness;
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
	bool isDimmable, isColor, isVariableColorTemp, isFactory;
	sLightState lightState;
	std::string discoVer;
	std::vector<sPreferredState> preferredStates;
	bool lightOn;
	std::string lightMode;
	int hue, saturation, color_temp, brightness;
};