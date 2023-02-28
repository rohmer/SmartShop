#pragma once

#include <string>
#include <vector>

#include "CPUInfo.h"
#include "DeviceBase.h"

class HostRegistration
{
public:
	HostRegistration();
	void AddDevice(DeviceBase *device);
	
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
	
private:
	HostRegistration(std::string hostname, std::string cpuID, EPIType deviceType, uint cpuCount);
	
	std::string cpuID;
	std::string hostname;
	EPIType deviceType;
	uint cpuCount;
	
	struct sDevice
	{
	public:
		eDeviceBus deviceBus;
		eDeviceType deviceType;
		std::string deviceName;
		std::string deviceDescription;
		DeviceConfig deviceConfig;
	};
	std::vector<sDevice> devices;
	
	cJSON *deviceToJSON(sDevice device);
	static sDevice deviceFromJSON(cJSON *json);
	void addDevReg(sDevice device);
};