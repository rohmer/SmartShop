#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "../Logger/LogMsg.h"
#include "DBEventData.h"
#include "DBSwitchData.h"
#include "DBVectorData.h"
#include "DBColorData.h"
#include "DBIntData.h"
#include "DBStringData.h"
#include "DBFloatData.h"
#include "DBBinaryData.h"
#include "DBDeviceConfig.h"
#include "DBDeviceConfigItem.h"
#include "DB.h"
#include <sqlite_orm.h>

inline auto initCoreStorage(const std::string &path)
{
	using namespace sqlite_orm;
	return make_storage(path,
		make_table("Log",
			make_column("id", &LogMsg::ID, primary_key().autoincrement()),
			make_column("time", &LogMsg::Timestamp),
			make_column("msg", &LogMsg::Message),
			make_column("severity", &LogMsg::Severity),
			make_column("host", &LogMsg::Host)),
		make_table("SensorEvents",
			make_column("id", &DBEventData::ID, primary_key().autoincrement()),
			make_column("sensorName", &DBEventData::SensorName),
			make_column("host", &DBEventData::Hostname),
			make_column("time", &DBEventData::EventTime)),
		make_table("SwitchData",
			make_column("id", &DBSwitchData::ID,primary_key().autoincrement()),
			make_column("eventID", &DBSwitchData::EventID),
			make_column("switchID", &DBSwitchData::SwitchID),
			make_column("value", &DBSwitchData::Value)),
		make_table("VectorData",
			make_column("id",&DBVectorData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBVectorData::EventID),
			make_column("x", &DBVectorData::X),
			make_column("y", &DBVectorData::Y),
			make_column("z", &DBVectorData::Z),
			make_column("roll", &DBVectorData::Roll),
			make_column("pitch", &DBVectorData::Pitch),
			make_column("heading", &DBVectorData::Heading)),
		make_table("ColorData",
			make_column("id",&DBColorData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBColorData::EventID),
			make_column("red",&DBColorData::Red),
			make_column("green",&DBColorData::Green),
			make_column("blue",&DBColorData::Blue),
			make_column("alpha",&DBColorData::Alpha)),
		make_table("IntData",
			make_column("id",&DBIntData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBIntData::EventID),
			make_column("name", &DBIntData::Name),
			make_column("value", &DBIntData::Value)),
		make_table("StringData",
			make_column("id",&DBStringData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBStringData::EventID),
			make_column("name", &DBStringData::Name),
			make_column("value", &DBStringData::Value)),
		make_table("FloatData",
			make_column("id",&DBFloatData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBFloatData::EventID),
			make_column("name", &DBFloatData::Name),
			make_column("value", &DBFloatData::Value)),
		make_table("BinaryData",
			make_column("id",&DBBinaryData::ID, primary_key().autoincrement()),
			make_column("eventID", &DBBinaryData::EventID),
			make_column("name", &DBBinaryData::Name),
			make_column("value", &DBBinaryData::Data)),
		make_table("DeviceConfig",
			make_column("id", &DBDeviceConfig::ID, primary_key().autoincrement()),
			make_column("hostname", &DBDeviceConfig::Hostname),
			make_column("deviceName", &DBDeviceConfig::DeviceName),
			make_column("deviceDesc", &DBDeviceConfig::DeviceDescription),
			make_column("deviceBus", &DBDeviceConfig::DeviceBus),
			make_column("deviceType", &DBDeviceConfig::DeviceType)),
		make_table("DeviceConfigItem",
			make_column("id", &DBDeviceConfigItem::ID, primary_key().autoincrement()),
			make_column("deviceID", &DBDeviceConfigItem::DeviceID), 
			make_column("dataType", &DBDeviceConfigItem::DataType),
			make_column("deviceName", &DBDeviceConfigItem::Name),
			make_column("value", &DBDeviceConfigItem::Value),
			make_column("ro", &DBDeviceConfigItem::ReadOnly))			
		);
}
	
class DB
{
private:
	using Storage = decltype(initCoreStorage(""));
	
public:
	static DB *GetInstance(std::string path = "");
	
	std::shared_ptr<Storage> GetStorage()
	{
		if (!initialized)
		{
			init();
			initialized = true;
		}
		return storage;
	}
private:
	DB(std::string path = "");
	static DB* instance;	
	
	std::shared_ptr<Storage> storage;
	bool initialized = false;
	
	void init();
	std::string path;
};