#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <Scheduler.h>

#include "DeviceBase.h"
#include "Sensor.h"
#include "DeviceConfig.h"
#include "../Logger/Logger.h"
#include "pigpio.h"

class DeviceManager
{
public:
	static DeviceManager *GetInstance();
	~DeviceManager();
	void AddDevice(DeviceBase *device);
	
	std::vector<DeviceBase*> GetDeviceByType(eDeviceType deviceType);
	DeviceBase* GetDeviceByName(std::string name);
	std::vector<DeviceBase*> GetDeviceByBus(eDeviceBus deviceBus);
	
private:
	static DeviceManager *instance;
	DeviceManager();
	
	
	Logger *log;
	Bosma::Scheduler *scheduler;
	
	std::map<eDeviceBus, std::vector<DeviceBase*>> deviceByBus;
	std::map<eDeviceType, std::vector<DeviceBase*>> deviceByType;
	std::map<std::string, DeviceBase*> deviceByName;
	std::map<std::string, DeviceConfig> deviceConfigs;
	void scheduleSensor(Sensor *sensor);
	void rescheduleSensors();
	
	bool storeConfig();
	bool loadConfig();
};