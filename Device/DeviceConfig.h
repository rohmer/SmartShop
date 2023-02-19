#pragma once

#include <string>
#include <vector>
#include <unistd.h>

#include <cjson/cJSON.h>
#include "../DB/DB.h"
#include "CPUInfo.h"
#include "DeviceConfigItem.h"
#include "DeviceEnums.h"
#include "DBDeviceConfig.h"
#include "DBDeviceConfigItem.h"

class DeviceConfig
{
public:	
	DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::string hostname="", std::string devID="");
	DeviceConfig(std::string DeviceName, std::string DeviceDescription, eDeviceBus DeviceBus, eDeviceType DeviceType, std::vector<DeviceConfigItem> &DeviceConfigItems, std::string hostname="");
	DeviceConfig();
	
	bool AddConfigItem(DeviceConfigItem item);
	std::vector<DeviceConfigItem> GetDeviceConfig();
	
	cJSON *ToJSON();
	static DeviceConfig FromJSON(cJSON *obj);
	
	std::string GetName();
	std::string GetDescription();
	eDeviceBus GetDeviceBus();
	eDeviceType GetDeviceType();
	
	DeviceConfigItem GetConfigItem(std::string name);
	void SetConfigItem(DeviceConfigItem item);
	bool HasConfigItem(DeviceConfigItem item);
	bool HasConfigItem(std::string name);
	
	bool ToDB();
	static DeviceConfig FromDB(std::string DeviceName, std::string Hostname);
	std::string GetHostname();
	
protected:
	std::vector<DeviceConfigItem> items;	
	std::string name, desc, deviceID;
	eDeviceBus bus;
	eDeviceType deviceType;
	std::string hostname;
};