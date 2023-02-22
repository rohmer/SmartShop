#pragma once
#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"

class SwitchData : public SensorDataBase
{
public:
	SwitchData(uint switchID, bool value);
	
	cJSON *ToJSON() override;
	static SwitchData *FromJSON(cJSON *JSON);
	
	void SetValue(bool val);
	void SetSwitchID(uint switchID);
	
	bool GetValue();
	uint GetSwitchID();
	void StoreToDB(unsigned long eventID) override;
	
private:
	uint id;
	bool val;
	
};