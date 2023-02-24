#include "SensorEvent.h"

SensorEvent::SensorEvent(std::string sensorName, std::string hostname, std::string hostID, time_t eventTime) :
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
	if (hostID.size() == 0)
	{
		this->hostID = CPUInfo::GetCPUID();
	}
	else
	{
		this->hostID = hostID;
	}
	
	
	if (eventTime == 0)
		this->eventTime = time(NULL);
	else
		this->eventTime = eventTime;
}

SensorEvent::~SensorEvent()
{
	for (int i = 0; i < sensorData.size(); i++)
		delete(sensorData[i]);
}
void SensorEvent::AddEventData(BinaryData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

void SensorEvent::AddEventData(ColorData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

void SensorEvent::AddEventData(FloatData *sensorEvent)
{
	sensorData.push_back(sensorEvent) ;
}

void SensorEvent::AddEventData(IntData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

void SensorEvent::AddEventData(StringData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

void SensorEvent::AddEventData(SwitchData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

void SensorEvent::AddEventData(VectorData *sensorEvent)
{
	sensorData.push_back(sensorEvent);
}

std::vector<SensorDataBase *> SensorEvent::GetEventData()
{
	return sensorData;
}

cJSON *SensorEvent::ToJSON()
{
	cJSON *evt = cJSON_CreateObject();
	cJSON_AddItemToObject(evt, "sensorName", cJSON_CreateString(sensorName.c_str()));
	cJSON_AddItemToObject(evt, "time", cJSON_CreateNumber(eventTime));
	cJSON_AddItemToObject(evt, "host", cJSON_CreateString(hostname.c_str()));
	cJSON_AddItemToObject(evt, "hostid", cJSON_CreateString(hostID.c_str()));
	cJSON *events = cJSON_CreateArray();
	
	for (int i=0; i<sensorData.size(); i++)
	{
		cJSON_AddItemToArray(events, sensorData[i]->ToJSON());
	}
	
	cJSON_AddItemToObject(evt, "events", events);
	
	return evt;
}

SensorEvent SensorEvent::FromJSON(cJSON *json)
{
	std::string name, host, hostid;
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
	if (cJSON_HasObjectItem(json, "hostid"))
	{
		hostid = cJSON_GetObjectItem(json, "hostid")->valuestring;
	}
	
	SensorEvent evt(name, host, hostid,eventTime);
	
	if (cJSON_HasObjectItem(json, "events"))
	{
		cJSON *events = cJSON_GetObjectItem(json, "events");
		cJSON *event;
		cJSON_ArrayForEach(event, events)
		{
			std::string jsonStr(cJSON_Print(event));
			if (cJSON_HasObjectItem(event, "type"))
			{
				eSensorDataTypes dt = (eSensorDataTypes)(cJSON_GetObjectItem(event, "type")->valueint);
				switch (dt)
				{
				case SWITCH:			
					{
					SwitchData* sdb = SwitchData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case VECTOR:
					{
						VectorData* sdb = VectorData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case COLOR:
					{
						ColorData *sdb = ColorData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case INTEGER:
					{
						IntData *sdb = IntData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case FLOAT:
					{
						FloatData *sdb = FloatData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case STRING:
					{
						StringData *sdb = StringData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				case BINARY:
					{
						BinaryData *sdb = BinaryData::FromJSON(event);
						evt.AddEventData(sdb);
						break;
					}
				}
			}
		}
	}
	
	return evt;
}

SensorEvent SensorEvent::GetFromDB(unsigned int eventID)
{
	using namespace sqlite_orm;
	std::vector<DBEventData> evts = DB::GetInstance()->GetStorage()->get_all<DBEventData>(where(c(&DBEventData::ID) == eventID));
	if (evts.size() == 0)
		return SensorEvent();
	SensorEvent se(evts[0].SensorName, evts[0].Hostname, evts[0].HostID, evts[0].EventTime);
	se.GetSensorData(eventID);
	return se;
}

void SensorEvent::StoreToDB()
{
	DBEventData evt;
	evt.Hostname = hostname;
	evt.SensorName = sensorName;
	evt.EventTime = eventTime;
	evt.HostID = hostID;
	
	unsigned long eventID = DB::GetInstance()->GetStorage()->insert(evt);
	for (int i=0; i<sensorData.size(); i++)
	{
		try
		{
			sensorData[i]->StoreToDB(eventID);
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

void SensorEvent::GetSensorData(unsigned int eventID)
{
	// TODO: I really dont like how this is
	using namespace sqlite_orm;
	std::vector<DBBinaryData> binDat=DB::GetInstance()->GetStorage()->get_all<DBBinaryData>(where(c(&DBBinaryData::EventID) == eventID));
	for (std::vector<DBBinaryData>::iterator it = binDat.begin(); it != binDat.end(); ++it)
	{
		BinaryData *bd = new BinaryData(it->Name, it->Data);
		AddEventData(bd);
	}
	std::vector<DBColorData> colDat= DB::GetInstance()->GetStorage()->get_all<DBColorData>(where(c(&DBColorData::EventID) == eventID));
	for (std::vector<DBColorData>::iterator it = colDat.begin(); it != colDat.end(); ++it)
	{
		ColorData*cd = new ColorData(it->Red,it->Green,it->Blue,it->Alpha);
		AddEventData(cd);
	}
	std::vector<DBFloatData> floatDat = DB::GetInstance()->GetStorage()->get_all<DBFloatData>(where(c(&DBFloatData::EventID) == eventID));
	for (std::vector<DBFloatData>::iterator it = floatDat.begin(); it != floatDat.end(); ++it)
	{
		FloatData *fd = new FloatData(it->Name, it->Value);
		AddEventData(fd);
	}
	std::vector<DBIntData> intDat = DB::GetInstance()->GetStorage()->get_all<DBIntData>(where(c(&DBIntData::EventID) == eventID));
	for (std::vector<DBIntData>::iterator it = intDat.begin(); it != intDat.end(); ++it)
	{
		IntData *id=new IntData(it->Name, it->Value);
		AddEventData(id);
	}
	std::vector<DBStringData> strDat = DB::GetInstance()->GetStorage()->get_all<DBStringData>(where(c(&DBStringData::EventID) == eventID));
	for (std::vector<DBStringData>::iterator it = strDat.begin(); it != strDat.end(); ++it)
	{
		StringData *sd = new StringData(it->Name,it->Value);
		AddEventData(sd);
	}
	std::vector<DBSwitchData> swDat = DB::GetInstance()->GetStorage()->get_all<DBSwitchData>(where(c(&DBSwitchData::EventID) == eventID));
	for (std::vector<DBSwitchData>::iterator it = swDat.begin(); it != swDat.end(); ++it)
	{
		SwitchData *sd = new SwitchData(it->SwitchID, it->Value);
		AddEventData(sd);
	}
	std::vector<DBVectorData> vecDat = DB::GetInstance()->GetStorage()->get_all<DBVectorData>(where(c(&DBVectorData::EventID) == eventID));
	for (std::vector<DBVectorData>::iterator it = vecDat.begin(); it != vecDat.end(); ++it)
	{
		VectorData *vd = new VectorData(it->X, it->Y, it->Z, it->Roll, it->Heading, it->Pitch);
		AddEventData(vd);
	}
}

