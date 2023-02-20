#include "SensorEvent.h"

SensorEvent::SensorEvent(std::string sensorName, std::string hostname, time_t eventTime) :
	sensorName(sensorName)
{
	if (hostname.size() == 0)
	{
		char hostname[1024];
		gethostname(hostname, 1024);
		std::string host(hostname);
		this->hostname = host;
	}
	else
	{
		this->hostname = hostname;
	}
	
	if (eventTime == 0)
		this->eventTime = time(NULL);
	else
		this->eventTime = eventTime;
}

void SensorEvent::AddEventData(BinaryData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(ColorData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(FloatData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(IntData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(StringData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(SwitchData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

void SensorEvent::AddEventData(VectorData sensorEvent)
{
	sensorData.push_back((SensorDataBase)sensorEvent);
}

std::vector<SensorDataBase> SensorEvent::GetEventData()
{
	return sensorData;
}

cJSON *SensorEvent::ToJSON()
{
	cJSON *evt = cJSON_CreateObject();
	cJSON_AddItemToObject(evt, "sensorName", cJSON_CreateString(sensorName.c_str()));
	cJSON_AddItemToObject(evt, "time", cJSON_CreateNumber(eventTime));
	cJSON_AddItemToObject(evt, "host", cJSON_CreateString(hostname.c_str()));
	
	cJSON *events = cJSON_CreateArray();
	
	for (std::vector<SensorDataBase>::iterator it = sensorData.begin(); it != sensorData.end(); it++)
	{
		cJSON_AddItemToArray(events, it->ToJSON());
	}
	
	cJSON_AddItemToObject(evt, "events", events);
	
	return evt;
}

SensorEvent SensorEvent::FromJSON(cJSON *json)
{
	std::string name, host;
	time_t eventTime;
	
	if (cJSON_HasObjectItem(json, "sensorName"))
	{
		name = cJSON_GetObjectItem(json, "sensorName")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "time"))
	{
		eventTime = cJSON_GetObjectItem(json, "time")->valueint;
	}
	if (cJSON_HasObjectItem(json,"host"))
	{
		host = cJSON_GetObjectItem(json, "host")->valuestring;
	}
	
	SensorEvent evt(name, host, eventTime);
	
	if (cJSON_HasObjectItem(json, "events"))
	{
		cJSON *events = cJSON_GetObjectItem(json, "events");
		cJSON *event;
		cJSON_ArrayForEach(event, events)
		{
			if (cJSON_HasObjectItem(event, "type"))
			{
				eSensorDataTypes dt = (eSensorDataTypes)cJSON_GetObjectItem(json, "type")->valueint;
				switch (dt)
				{
				case SWITCH:			
					{
					SwitchData sdb = SwitchData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case VECTOR:
					{
						VectorData sdb = VectorData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case COLOR:
					{
						ColorData sdb = ColorData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case INTEGER:
					{
						IntData sdb = IntData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case FLOAT:
					{
						FloatData sdb = FloatData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case STRING:
					{
						StringData sdb = StringData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case BINARY:
					{
						BinaryData sdb = BinaryData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				}
			}
		}
	}
	
	return evt;
}

void SensorEvent::StoreToDB()
{
	DBEventData evt;
	evt.Hostname = hostname;
	evt.SensorName = sensorName;
	evt.EventTime = eventTime;
	
	unsigned long eventID = DB::GetInstance()->GetStorage()->insert(evt);
	for (std::vector<SensorDataBase>::iterator it = sensorData.begin(); it != sensorData.end(); ++it)
	{
		try
		{
			it->StoreToDB(eventID);
		}
		catch (const std::exception &e)
		{
			std::stringstream ss;
			ss << "Failed to store event: " << e.what();
			Logger::GetInstance()->LogC(ss.str());
		}
	}
}

bool SensorEvent::SendToServer(std::string serverResource)
{
	cJSON *evt = ToJSON();
	if (evt == NULL)
	{
		Logger::GetInstance()->LogW("Failed to serialize event");
		return false;
	}
	
	return false;
	
}