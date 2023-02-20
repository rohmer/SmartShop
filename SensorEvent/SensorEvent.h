#pragma once

#include <string>
#include <unistd.h>
#include <vector>
#include <atomic>
#include "Logger.h"
#include "DB.h"
#include "SensorDataBase.h"
#include "SwitchData.h"
#include "VectorData.h"
#include "ColorData.h"
#include "IntData.h"
#include "FloatData.h"
#include "StringData.h"
#include "BinaryData.h"


class SensorEvent
{
public:
	SensorEvent(std::string sensorName, std::string hostname = "", time_t eventTime=0);

	void AddEventData(BinaryData sensorData);
	void AddEventData(ColorData sensorData);
	void AddEventData(FloatData sensorData);
	void AddEventData(IntData  sensorData);
	void AddEventData(StringData sensorData);
	void AddEventData(SwitchData sensorData);
	void AddEventData(VectorData sensorData);
	
	
	std::vector<SensorDataBase> GetEventData();
	
	cJSON *ToJSON();
	
	static SensorEvent FromJSON(cJSON *json);
	
	void StoreToDB();
	bool SendToServer(std::string serverResource);
	
private:
	std::string hostname, sensorName;
	time_t eventTime;
	std::vector<SensorDataBase> sensorData;
};

