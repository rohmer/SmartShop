#include "DeviceConfig.h"

DeviceConfig::DeviceConfig()
{
	this->hostID = CPUInfo::GetCPUID();	
	this->deviceID = CPUInfo::GetCPUID();
}

DeviceConfig::DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::string hostname, std::string hostID)
	: name(DeviceName)
	, desc(DeviceDescription)
	, bus(DeviceBus)
	, deviceType(DeviceType)
{
	if (hostID.size() == 0)
	{
		this->hostID = CPUInfo::GetCPUID();
	}
	if (hostname.size() == 0)
	{
		char chost[1024];
		gethostname(chost, 1024);
		std::string hostname(chost);
	}
}

DeviceConfig::DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::vector<DeviceConfigItem> &DeviceConfigItems, std::string hostname, std::string hostID)
	: name(DeviceName)
	, desc(DeviceDescription)
	, bus(DeviceBus)
	, deviceType(DeviceType)
{
	for(int i=0; i<DeviceConfigItems.size(); i++)
	{
		items.push_back(DeviceConfigItems[i]);			
	}
	if (hostID.size() == 0)
	{
		this->hostID = CPUInfo::GetCPUID();
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

void DeviceConfig::DeleteConfigItem(std::string name)
{
	if (!HasConfigItem(name))
		return;
	int pos = -1;
	for (int i = 0; i < items.size(); i++)
		if (std::strcmp(items[i].GetName().c_str(), name.c_str()) == 0)
		{
			pos = i;
			break;
		}
	if(pos!=-1)
		items.erase(items.begin() + pos);
}

cJSON *DeviceConfig::ToJSON()
{
	cJSON *obj = cJSON_CreateObject();	
	cJSON_AddItemToObject(obj, "bus", cJSON_CreateNumber(bus));
	cJSON_AddItemToObject(obj, "type", cJSON_CreateNumber(deviceType));
	cJSON_AddItemToObject(obj, "devid", cJSON_CreateString(deviceID.c_str()));	
	cJSON_AddItemToObject(obj, "hostid", cJSON_CreateString(hostID.c_str()));
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString(name.c_str()));
	cJSON_AddItemToObject(obj, "desc", cJSON_CreateString(desc.c_str()));
	cJSON *arr = cJSON_CreateArray();
	for (std::vector<DeviceConfigItem>::iterator it = items.begin(); it != items.end(); it++)
		cJSON_AddItemToArray(arr, it->ToJSON());
	
	cJSON_AddItemToObject(obj, "config", arr);	
	return obj;		
}

DeviceConfig DeviceConfig::FromJSON(cJSON* obj)
{
	std::string name, desc, hostname, devid, hostID;
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
	if (cJSON_HasObjectItem(obj, "hostid"))
	{
		hostID = cJSON_GetObjectItem(obj, "hostid")->valuestring;
	}
	DeviceConfig ret(name, desc, bus, dType,hostname,hostID);
	ret.SetDeviceID(devid);
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
		dbdc.CPUID = hostID;
		
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
			item.hostID = hostID;
			switch (it->GetDataType())
			{
			case eConfigDataType::C_FLOAT:
				{
					std::stringstream ss;
					ss << it->GetFloatMax();
					item.Max = ss.str();
					ss.str("");
					ss << it->GetFloatMin();
					item.Min = ss.str();					
				}
				break;
			case eConfigDataType::C_LONG:
				{
					std::stringstream ss;
					ss << it->GetLongMax();
					item.Max = ss.str();
					ss.str("");
					ss << it->GetLongMin();
					item.Min = ss.str();		
				}
			default:
				break;
			}
			item.ID = DB::GetInstance()->GetStorage()->insert<DBDeviceConfigItem>(item);
			if (it->GetDataType() == eConfigDataType::C_STR && it->GetLegalStringValues().size() > 0)
			{
				std::vector<std::string> values = it->GetLegalStringValues();
				for (int i = 0; i < values.size(); i++)
				{
					DBStringLegalValues dbslv;
					dbslv.StringDataID = item.ID;
					dbslv.Value = values[i];
					dbslv.ID = DB::GetInstance()->GetStorage()->insert<DBStringLegalValues>(dbslv);
				}
			}
		}
		return true;
	}
	catch (std::exception &e)
	{
		return false;
	}
}

std::vector<DeviceConfig> DeviceConfig::FromDB(std::string CPUID)
{
	using namespace sqlite_orm;
	std::vector<DeviceConfig> ret;
	std::vector<DBDeviceConfig> dbdev=DB::GetInstance()->GetStorage()->get_all<DBDeviceConfig>(where(c(&DBDeviceConfig::CPUID)==CPUID));
	for (std::vector<DBDeviceConfig>::iterator it = dbdev.begin();
		it != dbdev.end();
		++it)
	{
		std::vector<DBDeviceConfigItem> dcis = DB::GetInstance()->GetStorage()->get_all<DBDeviceConfigItem>
			(where(c(&DBDeviceConfigItem::DeviceID) == it->DeviceID));
		// Next create the DeviceConfigItems in a vector and pass it to the DC constructor
		std::vector<DeviceConfigItem> deviceConfigs;
		for (std::vector<DBDeviceConfigItem>::iterator it = dcis.begin();
			it != dcis.end();
			++it)
		{
			DeviceConfigItem dci;
			switch (it->DataType)
			{
			case eConfigDataType::C_BOOL:
				{
					if (std::strcmp(it->Value.c_str(), "1") == 0)
						dci = DeviceConfigItem(it->Name, true, it->ReadOnly);
					else
						dci = DeviceConfigItem(it->Name, false, it->ReadOnly);
					break;
				}
			case eConfigDataType::C_FLOAT:
				{
					float val = std::atof(it->Value.c_str());
					float max = std::atof(it->Max.c_str());
					float min = std::atof(it->Min.c_str());
					dci = DeviceConfigItem(it->Name, val, max, min, it->ReadOnly);
					break;
				}
			case eConfigDataType::C_LONG:
				{
					long val = std::atol(it->Value.c_str());
					long max = std::atof(it->Max.c_str());
					long min = std::atof(it->Min.c_str());
					dci = DeviceConfigItem(it->Name, val, max, min, it->ReadOnly);
				}
			case eConfigDataType::C_STR:
				{
					using namespace sqlite_orm;
					std::vector<DBStringLegalValues> slv=DB::GetInstance()->GetStorage()->get_all<DBStringLegalValues>(where(c(&DBStringLegalValues::StringDataID) == it->ID));
					std::vector<std::string> lval;
					if (slv.size() > 0)
					{
						for (int i = 0; i < slv.size(); i++)
							lval.push_back(slv[i].Value);
					}
					dci=DeviceConfigItem(it->Name, it->Value,lval,it->ReadOnly);	
				}
			}
			deviceConfigs.push_back(dci);
		}
		std::stringstream ss;
		ss << it->ID;
		DeviceConfig dc(
			it->DeviceName,
			it->DeviceDescription,
			(eDeviceBus)it->DeviceBus, 
			(eDeviceType)it->DeviceType, 
			deviceConfigs, 
			it->Hostname, 
			ss.str());
		ret.push_back(dc);
	}
}