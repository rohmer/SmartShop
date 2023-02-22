#pragma once

#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"

class FloatData : public SensorDataBase
{
public:
	FloatData(std::string Name, float Value);
	
	cJSON *ToJSON() override;
	static FloatData *FromJSON(cJSON *json);
	
	void SetName(std::string value)
	{
		name = value;
	}
	void SetValue(float value)
	{
		this->value = value;
	}
	
	std::string GetName()
	{
		return name;
	}
	float GetValue()
	{
		return value;
	}
	void StoreToDB(unsigned long eventID) override;
private:
	std::string name;
	float value;
};
	