#pragma once

#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"
#include "DBBinaryData.h"
#include <base64.h>

class BinaryData : public SensorDataBase
{
public:
	BinaryData(std::string Name, std::string Data);
	
	cJSON *ToJSON() override;
	static BinaryData FromJSON(cJSON *json);
	
	std::string GetName()
	{
		return name;
	}
	
	std::string GetData()
	{
		return data;
	}
	
	void SetName(std::string value)
	{
		name = value;
	}
	
	void SetValue(std::string value)
	{
		this->data = value;
	}
	
	void StoreToDB(unsigned long eventID) override;
	
private:
	std::string name, data;
};