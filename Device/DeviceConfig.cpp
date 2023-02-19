#include "DeviceConfig.h"

DeviceConfig::DeviceConfig()
{
}

DeviceConfig::DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::string hostname, std::string devID)
	: name(DeviceName)
	, desc(DeviceDescription)
	, bus(DeviceBus)
	, deviceType(DeviceType)
	, deviceID(devID)
{
	if (devID.size() == 0)
	{
		devID = CPUInfo::GetCPUID();
	}

	if (hostname.size() == 0)
	{
		char chost[1024];
		gethostname(chost, 1024);
		std::string hostname(chost);
	}
}

DeviceConfig::DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::vector<DeviceConfigItem> &DeviceConfigItems, std::string hostname)
	: name(DeviceName)
	, desc(DeviceDescription)
	, bus(DeviceBus)
	, deviceType(DeviceType)
{
	for(int i=0; i<DeviceConfigItems.size(); i++)
	{
		items.push_back(DeviceConfigItems[i]);			
	}
	if (hostname.size() == 0)
	{
		char chost[1024];
		gethostname(chost, 1024);
		std::string hostname(chost);
	}
}

bool DeviceConfig::AddConfigItem(DeviceConfigItem item)
{
	for(std::vector<DeviceConfigItem>::iterator it=items.begin(); it!=items.end(); it++)	
		if(strcmp(it->GetName().c_str(),item.GetName().c_str())==0)
			return false;
	items.push_back(item);
	return true;
}

std::vector<DeviceConfigItem> DeviceConfig::GetDeviceConfig()
{
	return items;
}

std::string DeviceConfig::GetHostname()
{
	return hostname;
}	

std::string DeviceConfig::GetName()
{
	return name;
}

std::string DeviceConfig::GetDescription()
{
	return desc;
}

eDeviceBus DeviceConfig::GetDeviceBus()
{
	return bus;
}

eDeviceType DeviceConfig::GetDeviceType()
{
	return deviceType;
}

DeviceConfigItem DeviceConfig::GetConfigItem(std::string name)
{
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		if (strcmp(it->GetName().c_str(), name.c_str()) == 0)
			return *it;
	return DeviceConfigItem();
}

void DeviceConfig::SetConfigItem(DeviceConfigItem item)
{
	std::vector<DeviceConfigItem> copy;
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		if (strcmp(it->GetName().c_str(), name.c_str()) != 0)
			copy.push_back(*it);
	copy.push_back(item);
	items.clear();
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		items.push_back(*it);
}

bool DeviceConfig::HasConfigItem(std::string name)
{ 
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		if (strcmp(it->GetName().c_str(), name.c_str()) == 0)
			return true;
	return false;
}

cJSON *DeviceConfig::ToJSON()
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(obj, "desc", cJSON_CreateString(desc.c_str()));
	cJSON_AddItemToObject(obj, "bus", cJSON_CreateNumber(bus));
	cJSON_AddItemToObject(obj, "type", cJSON_CreateNumber(deviceType));
	cJSON_AddItemToObject(obj, "host", cJSON_CreateString(hostname.c_str()));
	cJSON_AddItemToObject(obj, "devid", cJSON_CreateString(deviceID.c_str()));
	cJSON *arr = cJSON_CreateArray();
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		cJSON_AddItemToArray(arr, it->ToJSON());
	
	cJSON_AddItemToObject(obj, "config", arr);	
	return obj;		
}

DeviceConfig DeviceConfig::FromJSON(cJSON* obj)
{
	std::string name, desc, hostname, devid;
	eDeviceBus bus;
	eDeviceType dType;
	if (cJSON_HasObjectItem(obj, "name"))
	{
		name = cJSON_GetObjectItem(obj, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(obj, "desc"))
	{
		desc = cJSON_GetObjectItem(obj, "desc")->valuestring;
	}
	if (cJSON_HasObjectItem(obj, "bus"))
	{
		bus = (eDeviceBus)cJSON_GetObjectItem(obj, "bus")->valueint;
	}
	if (cJSON_HasObjectItem(obj, "type"))
	{
		dType = (eDeviceType)cJSON_GetObjectItem(obj, "type")->valueint;
	}
	if (cJSON_HasObjectItem(obj, "hostname"))
	{
		hostname = cJSON_GetObjectItem(obj, "host")->valuestring;
	}

	if (cJSON_HasObjectItem(obj, "devid"))
	{
		devid = cJSON_GetObjectItem(obj, "devid")->valuestring;
	}

	DeviceConfig ret(name, desc, bus, dType,hostname,devid);
	if (cJSON_HasObjectItem(obj, "config"))
	{
		cJSON *arr = cJSON_GetObjectItem(obj, "config");
		if (cJSON_IsArray(arr))
		{
			cJSON *ci;
			cJSON_ArrayForEach(ci, arr)
			{
				DeviceConfigItem item = DeviceConfigItem::FromJSON(ci);
				ret.AddConfigItem(item);
			}
		}
	}
	return ret;
	
}

bool DeviceConfig::HasConfigItem(DeviceConfigItem item)
{
	return HasConfigItem(item.GetName());
}

bool DeviceConfig::ToDB()
{
	try
	{
		// First we find if our DeviceConfig exists
		using namespace sqlite_orm;
		DBDeviceConfig dbdc;
		bool update = false;
		long dbConfigID;
		std::vector<DBDeviceConfig> dcs = DB::GetInstance()->GetStorage()->get_all<DBDeviceConfig>(where(c(&DBDeviceConfig::DeviceName) == name and c(&DBDeviceConfig::Hostname) == hostname));
		if (dcs.size() > 0)
		{
			dbdc.ID = dcs[0].ID;
			update = true;
			dbConfigID = dbdc.ID;
		}
		else
		{
			dbConfigID = -1;
		}
		dbdc.DeviceBus = (int)bus;
		dbdc.DeviceDescription = desc;
		dbdc.DeviceName = name;
		dbdc.DeviceType = (int)deviceType;
		dbdc.Hostname = hostname;
		dbdc.DeviceID = deviceID;
		
		if (update)
		{
			DB::GetInstance()->GetStorage()->update<DBDeviceConfig>(dbdc);
		}
		else
		{
			dbConfigID = DB::GetInstance()->GetStorage()->insert<DBDeviceConfig>(dbdc);
		}
	
		// We can remove all of the current instances of the config items, and update with the fresh ones
		DB::GetInstance()->GetStorage()->remove_all<DBDeviceConfigItem>(where(c(&DBDeviceConfigItem::DeviceID) == dbConfigID));
		for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); ++it)
		{
			DBDeviceConfigItem item;
			item.DataType = (int)it->GetDataType();
			item.DeviceID = dbConfigID;
			item.Name = it->GetName();
			item.ReadOnly = it->IsReadOnly();
			item.Value = it->GetStringVal();
			item.DeviceID = it->GetStringVal();
			item.ID = -1;
			int v = DB::GetInstance()->GetStorage()->insert<DBDeviceConfigItem>(item);
		}
		return true;
	}
	catch (std::exception &e)
	{
		return false;
	}
	
}