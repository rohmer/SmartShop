#pragma once

#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"

class StringData : public SensorDataBase
{
public:
	StringData(std::string Name, std::string Value);
	
	cJSON *ToJSON() override;
	static StringData FromJSON(cJSON *json);
	
	void SetName(std::string value)
	{
		name = value;
	}
	void SetValue(std::string value)
	{
		this->value = value;
	}
	
	std::string GetName()
	{
		return name;
	}
	std::string GetValue()
	{
		return value;
	}
	void StoreToDB(unsigned long eventID) override;
	
private:
	std::string name;
	std::string value;
};
	