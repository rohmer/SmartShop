#include "SensorEvent.h"

SensorEvent::SensorEvent(std::string sensorName, std::string hostname, std::string hostID, time_t eventTime, time_t groupNum)
	: sensorName(sensorName)
{
	groupID = groupNum;
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

void SensorEvent::AddEventData(BinaryData sensorEvent)
{
	
	sensorData.push_back(new BinaryData(sensorEvent.GetName(),sensorEvent.GetData()));
}

void SensorEvent::AddEventData(ColorData sensorEvent)
{
	sensorData.push_back(new ColorData(sensorEvent.GetRed(), sensorEvent.GetGreen(),sensorEvent.GetBlue(),sensorEvent.GetAlpha()));
}

void SensorEvent::AddEventData(FloatData sensorEvent)
{
	sensorData.push_back(new FloatData(sensorEvent.GetName(),sensorEvent.GetValue()));
}

void SensorEvent::AddEventData(IntData sensorEvent)
{
	sensorData.push_back(new IntData(sensorEvent.GetName(),sensorEvent.GetValue()));
}

void SensorEvent::AddEventData(StringData sensorEvent)
{
	sensorData.push_back(new StringData(sensorEvent.GetName(),sensorEvent.GetValue()));
}

void SensorEvent::AddEventData(SwitchData sensorEvent)
{
	sensorData.push_back(new SwitchData(sensorEvent.GetSwitchID(), sensorEvent.GetValue()));
}

void SensorEvent::AddEventData(VectorData sensorEvent) 
{
	sensorData.push_back(new VectorData(
		sensorEvent.GetX(),
		sensorEvent.GetY(),
		sensorEvent.GetZ(),
		sensorEvent.GetRoll(),
		sensorEvent.GetPitch(),
		sensorEvent.GetHeading()
		)
	);
}

cJSON *SensorEvent::ToJSON()
{
	cJSON *evt = cJSON_CreateObject();
	cJSON_AddItemToObject(evt, "sensorName", cJSON_CreateString(sensorName.c_str()));
	cJSON_AddItemToObject(evt, "time", cJSON_CreateNumber(eventTime));
	cJSON_AddItemToObject(evt, "host", cJSON_CreateString(hostname.c_str()));
	cJSON_AddItemToObject(evt, "hostid", cJSON_CreateString(hostID.c_str()));
	cJSON *events = cJSON_CreateArray();
	
	for (int i = 0; i < sensorData.size(); i++)
	{
		switch (sensorData[i]->GetDataType())
		{
		case eSensorDataTypes::SWITCH:
			{
				SwitchData *sdb = (SwitchData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::VECTOR:
			{
				VectorData *sdb = (VectorData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::COLOR:
			{
				ColorData *sdb = (ColorData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::INTEGER:
			{
				IntData *sdb = (IntData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::FLOAT:
			{
				FloatData *sdb = (FloatData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::STRING:
			{
				StringData *sdb = (StringData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		case eSensorDataTypes::BINARY:
			{
				BinaryData *sdb = (BinaryData*)sensorData[i];
				cJSON_AddItemToArray(events, sdb->ToJSON());
				break;
			}
		}		
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
	if (cJSON_HasObjectItem(json, "host"))
	{
		host = cJSON_GetObjectItem(json, "host")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "hostid"))
	{
		hostid = cJSON_GetObjectItem(json, "hostid")->valuestring;
	}
	
	SensorEvent evt(name, host, hostid, eventTime);
	
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

SensorEvent SensorEvent::GetFromDB(unsigned int eventID)
{
	using namespace sqlite_orm;
	std::vector<DBEventData> evts = DB::GetInstance()->GetStorage()->get_all<DBEventData>(where(c(&DBEventData::ID) == eventID));
	if (evts.size() == 0)
		return SensorEvent();
	SensorEvent se(evts[0].SensorName, evts[0].Hostname, evts[0].HostID, evts[0].EventTime, evts[0].EventGroup);

	std::vector<DBBinaryData> binDat = DB::GetInstance()->GetStorage()->get_all<DBBinaryData>(where(c(&DBBinaryData::EventID) == eventID));
	for (std::vector<DBBinaryData>::iterator it = binDat.begin(); it != binDat.end(); ++it)
	{
		BinaryData bd = BinaryData(it->Name, it->Data);
		se.AddEventData(bd);
	}
	std::vector<DBColorData> colDat = DB::GetInstance()->GetStorage()->get_all<DBColorData>(where(c(&DBColorData::EventID) == eventID));
	for (std::vector<DBColorData>::iterator it = colDat.begin(); it != colDat.end(); ++it)
	{
		ColorData cd = ColorData(it->Red, it->Green, it->Blue, it->Alpha);
		se.AddEventData(cd);
	}
	std::vector<DBFloatData> floatDat = DB::GetInstance()->GetStorage()->get_all<DBFloatData>(where(c(&DBFloatData::EventID) == eventID));
	for (std::vector<DBFloatData>::iterator it = floatDat.begin(); it != floatDat.end(); ++it)
	{
		FloatData fd = FloatData(it->Name, it->Value);
		se.AddEventData(fd);
	}
	std::vector<DBIntData> intDat = DB::GetInstance()->GetStorage()->get_all<DBIntData>(where(c(&DBIntData::EventID) == eventID));
	for (std::vector<DBIntData>::iterator it = intDat.begin(); it != intDat.end(); ++it)
	{
		IntData id = IntData(it->Name, it->Value);
		se.AddEventData(id);
	}
	std::vector<DBStringData> strDat = DB::GetInstance()->GetStorage()->get_all<DBStringData>(where(c(&DBStringData::EventID) == eventID));
	for (std::vector<DBStringData>::iterator it = strDat.begin(); it != strDat.end(); ++it)
	{
		StringData sd = StringData(it->Name, it->Value);
		se.AddEventData(sd);
	}
	std::vector<DBSwitchData> swDat = DB::GetInstance()->GetStorage()->get_all<DBSwitchData>(where(c(&DBSwitchData::EventID) == eventID));
	for (std::vector<DBSwitchData>::iterator it = swDat.begin(); it != swDat.end(); ++it)
	{
		SwitchData sd = SwitchData(it->SwitchID, it->Value);
		se.AddEventData(sd);
	}
	std::vector<DBVectorData> vecDat = DB::GetInstance()->GetStorage()->get_all<DBVectorData>(where(c(&DBVectorData::EventID) == eventID));
	for (std::vector<DBVectorData>::iterator it = vecDat.begin(); it != vecDat.end(); ++it)
	{
		VectorData vd =VectorData(it->X, it->Y, it->Z, it->Roll, it->Heading, it->Pitch);
		se.AddEventData(vd);
	}
	return se;
}

void SensorEvent::StoreToDB()
{
	DBEventData evt;
	evt.Hostname = hostname;
	evt.SensorName = sensorName;
	evt.EventTime = eventTime;
	evt.HostID = hostID;
	evt.EventGroup = groupID;
	evt.ID = -1;
	try
	{
		evt.ID = DB::GetInstance()->GetStorage()->insert(evt);	
	}
	catch (const std::exception&e)
	{
		std::stringstream ss;
		ss << "Failed to store event: " << e.what();
		std::string msg = ss.str();
		Logger::GetInstance()->LogC(msg);
	}
	
	for (int i = 0; i < sensorData.size(); i++)
	{
		try
		{			
			switch (sensorData[i]->GetDataType())
			{
			case eSensorDataTypes::SWITCH:
				{
					SwitchData *sdb = (SwitchData*)sensorData[i];
					sdb->StoreToDB(evt.ID);
					break;
				}
			case eSensorDataTypes::VECTOR:
				{
					VectorData *sdb = (VectorData*)sensorData[i];
					sdb->StoreToDB(evt.ID);
					break;
				}
			case eSensorDataTypes::COLOR:
				{
					ColorData *sdb = (ColorData*)sensorData[i];
					sdb->StoreToDB(evt.ID);
					break;
				}
			case eSensorDataTypes::INTEGER:
				{
					IntData *sdb = (IntData*)sensorData[i];
					sdb->StoreToDB(evt.ID);
					break;
				}
			case eSensorDataTypes::FLOAT:
				{
					FloatData *sdb = (FloatData*)sensorData[i];
					sdb->StoreToDB(evt.ID); 
					break;
				}
			case eSensorDataTypes::STRING:
				{
					StringData *sdb = (StringData*)sensorData[i];
					sdb->StoreToDB(evt.ID); 
					break;
				}
			case eSensorDataTypes::BINARY:
				{
					BinaryData *sdb = (BinaryData*)sensorData[i];
					sdb->StoreToDB(evt.ID);
					break;
				}
			}					
		}
		catch (const std::exception &e)
		{
			std::stringstream ss;
			ss << "Failed to store event: " << e.what();
			Logger::GetInstance()->LogC(ss.str());
		}
	}
}

unsigned long SensorEvent::StoreGroupToDB(std::vector<SensorEvent> sensorEventGroup)
{
	if (sensorEventGroup.size() == 0)
		return 0;
	unsigned long grpNum = sensorEventGroup[0].GetEventTime();
	for (int i = 0; i < sensorEventGroup.size(); i++)
	{
		sensorEventGroup[i].SetGroupID(grpNum);
		sensorEventGroup[i].StoreToDB();
	}
	return grpNum;
}

SensorEvent SensorEvent::GetLatestFromDB(std::string Hostname, std::string EventName)
{
	using namespace sqlite_orm;
	std::vector<DBEventData> evts = DB::GetInstance()->GetStorage()->get_all<DBEventData>(
		where(
			c(&DBEventData::Hostname)==Hostname and 
			c(&DBEventData::SensorName)==EventName
		), 
		order_by(&DBEventData::EventTime), 
		limit(1)
		);
	
	if(evts.size()>=1) // this should only be 1/0 but..  to be safe
	{
		return GetFromDB(evts[0].ID);
	} else
	{
		return SensorEvent();
	}				
}

std::vector<SensorEvent> SensorEvent::GetLatestGroupFromDB(std::string Hostname, std::string EventName)
{
	std::vector<SensorEvent> ret;
	SensorEvent se = GetLatestFromDB(Hostname, EventName);
	if (std::strcmp(se.hostname.c_str(), Hostname.c_str()) != 0)
		return ret;
	using namespace sqlite_orm;
	std::vector<DBEventData> evts = DB::GetInstance()->GetStorage()->get_all<DBEventData>(
		where(
			c(&DBEventData::EventGroup) == se.GetGroupID()
		));
	for (int i = 0; i < evts.size(); i++)
	{
		ret.push_back(GetFromDB(evts[i].ID));
	}
	return ret;
}

SensorEvent::~SensorEvent()
{	
	sensorData.clear();
}