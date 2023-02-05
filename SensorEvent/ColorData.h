#pragma once

#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"

class ColorData : public SensorDataBase
{
public:
	ColorData(float R = 0, float G = 0, float B = 0, float A = 0);
	cJSON *ToJSON() override;
	static ColorData FromJSON(cJSON *JSON);
	
	float GetRed()
	{
		return r;
	}
	float GetGreen()
	{
		return g;
	}
	float GetBlue()
	{
		return b;
	}
	float GetAlpha()
	{
		return a;
	}
	void SetRed(float value)
	{
		r = value;
	}
	void SetGreen(float value)
	{
		g = value;
	}
	void SetBlue(float value)
	{
		b = value;
	}
	void SetAlpha(float value)
	{
		a = value;
	}
	void StoreToDB(unsigned long eventID) override;
	
private:
	float r, g, b, a;
};