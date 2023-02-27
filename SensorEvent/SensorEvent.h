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
	SensorEvent()
	{
	}
	SensorEvent(std::string sensorName, std::string hostname = "", std::string hostID = "", time_t eventTime = 0);
	~SensorEvent();
	
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
	
	std::vector<SensorDataBase*> GetEventData() 
	{
		std::vector<SensorDataBase*> ret;
		for (int i = 0; i < sensorData.size(); i++)
		{
			SensorDataBase *ptr = sensorData[i];
			ret.push_back(ptr);
		}
		return ret;
	}
	
	void StoreToDB();

	static SensorEvent GetFromDB(unsigned int eventID);	
	cJSON *ToJSON();

	static SensorEvent FromJSON(cJSON *json);
	
	void AddEventData(BinaryData sensorEvent);
	void AddEventData(ColorData sensorEvent);
	void AddEventData(FloatData sensorEvent);
	void AddEventData(IntData sensorEvent);
	void AddEventData(StringData sensorEvent);
	void AddEventData(SwitchData sensorEvent);
	void AddEventData(VectorData sensorEvent);
	
private:
	std::string hostname, sensorName, hostID;
	time_t eventTime;
	std::vector<SensorDataBase*> sensorData;
};