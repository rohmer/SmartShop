#pragma once
#include <string>
#include "cJSON.h"
#include "SensorDataBase.h"

class SwitchData : public SensorDataBase
{
public:
	SwitchData(std::string Name, uint switchID, bool value);
	
	cJSON *ToJSON();
	static SwitchData FromJSON(cJSON *JSON);
	
	void SetValue(bool val);
	void SetSwitchID(uint switchID);
	
	bool GetValue();
	uint GetSwitchID();
	void StoreToDB(unsigned long eventID);
	
private:
	uint id;
	bool val;
	
};