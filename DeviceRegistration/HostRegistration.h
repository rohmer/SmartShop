#pragma once

#include <string>
#include <vector>
#include <sqlite_orm.h>

#include "CPUInfo.h"
#include "DeviceBase.h"
#include "DeviceManager.h"
#include "../../Config/Config.h"


class HostRegistration
{
public:	
	HostRegistration();
	
	cJSON *ToJSON();
	static HostRegistration FromJSON(cJSON *json);
	
	std::string GetCPUID()
	{
		return cpuID;
	}
	std::string GetHostname()
	{
		return hostname;
	}
	
	EPIType GetDeviceType()
	{
		return deviceType;
	}
	
	uint GetCPUCount()
	{
		return cpuCount;
	}
	
	std::vector<DeviceConfig> GetDevices()
	{
		return config.GetDevices();
	}
	
	void AddDevice(DeviceConfig dc)
	{
		config.AddDeviceConfig(dc);
	}
	
	std::string GetIPAddress()
	{
		return ipAddress;
	}
	
	bool GetIsAuth()
	{
		return isAuth;
	}
	
	bool StoreToDB();
	
	static HostRegistration FromDB(std::string cpuID);
	
private:
	HostRegistration(std::string hostname, std::string cpuID, EPIType deviceType, uint cpuCount, std::string ipAddr, bool auth=false);
	
	std::string cpuID;
	std::string hostname;
	EPIType deviceType;
	uint cpuCount;
	std::string ipAddress;
	static Config config;
	bool isAuth = false;
};