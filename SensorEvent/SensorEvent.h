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
#include "../RaspUtils/CPUInfo.h"


class SensorEvent
{
public:
	SensorEvent(std::string sensorName, std::string hostname = "", std::string hostID="", time_t eventTime=0);

	void AddEventData(BinaryData sensorData);
	void AddEventData(ColorData sensorData);
	void AddEventData(FloatData sensorData);
	void AddEventData(IntData  sensorData);
	void AddEventData(StringData sensorData);
	void AddEventData(SwitchData sensorData);
	void AddEventData(VectorData sensorData);
	
	
	std::vector<std::shared_ptr<SensorDataBase>> GetEventData() ;
	
	cJSON *ToJSON();
	
	static SensorEvent FromJSON(cJSON *json);
	
	void StoreToDB();
	bool SendToServer(std::string serverResource);

	std::string GetHostname()
	{
		return hostname;
	}
	std::string GetSensorName()
	{
		return sensorName;
	}
	std::string GetHostID()
	{
		return hostID;
	}
	time_t GetEventTime()
	{
		return eventTime;
	}
	
private:
	std::string hostname, sensorName, hostID;
	time_t eventTime;
	std::vector<std::shared_ptr<SensorDataBase>> sensorData;
};

