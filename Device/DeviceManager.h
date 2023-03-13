#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <vector>
#include <Scheduler.h>
#include <cjson/cJSON.h>

#include "DeviceBase.h"
#include "Sensor.h"
#include "DeviceConfig.h"
#include "../Logger/Logger.h"
#include "../Components/md5-master/md5.h"

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
	
	std::vector<std::string> GetServerEndpoints();
	void AddServerEndpoint(std::string server);
	
	std::vector<DeviceBase*> GetAllDevices();
	
	std::thread *updateThread;
	
	
private:
	static DeviceManager *instance;
	DeviceManager();
	void updateLoop();
	
	
	Logger *log;
	Bosma::Scheduler *scheduler;
	
	std::vector<std::string> serverEndpoints;
	std::map<eDeviceBus, std::vector<DeviceBase*>> deviceByBus;
	std::map<eDeviceType, std::vector<DeviceBase*>> deviceByType;
	std::map<std::string, DeviceBase*> deviceByName;
	std::map<std::string, DeviceConfig> deviceConfigs;
	std::vector<DeviceBase*> devices;
	void scheduleSensor(Sensor *sensor);
	void rescheduleSensors();
	
	bool storeConfig();
	bool loadConfig();
	bool shutdown = false;
};