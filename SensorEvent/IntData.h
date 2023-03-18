#pragma once

#include <string>
#include "cJSON.h"
#include "SensorDataBase.h"

class IntData : public SensorDataBase
{
public:
	IntData(std::string Name, long Value);
	
	cJSON *ToJSON();
	static IntData FromJSON(cJSON *json);
	
	void SetName(std::string value)
	{
		name = value;
	}
	void SetValue(long value)
	{
		this->value = value;
	}
	
	std::string GetName()
	{
		return name;
	}
	int GetValue()
	{
		return value;
	}
	void StoreToDB(unsigned long eventID);
	
private:	
	std::string name;
	long value;
};
	