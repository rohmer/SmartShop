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
	SensorEvent(std::string sensorName, std::string hostname = "", std::string hostID="", time_t eventTime=0);
	~SensorEvent();
	
	void AddEventData(BinaryData *sensorData);
	void AddEventData(ColorData *sensorData);
	void AddEventData(FloatData *sensorData);
	void AddEventData(IntData  *sensorData);
	void AddEventData(StringData *sensorData);
	void AddEventData(SwitchData *sensorData);
	void AddEventData(VectorData *sensorData);
	
	
	std::vector<SensorDataBase*> GetEventData() ;
	
	cJSON *ToJSON();
	
	static SensorEvent FromJSON(cJSON *json);
	
	void StoreToDB();
	
	static SensorEvent GetFromDB(unsigned int eventID);
	
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
	
	void GetSensorData(unsigned int EventID);

	
private:
	std::string hostname, sensorName, hostID;
	time_t eventTime;
	std::vector<SensorDataBase *> sensorData;
};

