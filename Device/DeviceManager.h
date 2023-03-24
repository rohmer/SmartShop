#pragma once

#include <filesystem>
#include <fstream>
#include <hash_map>
#include <string>
#include <map>
#include <thread>
#include <unordered_map>
#include <vector>
#include <Scheduler.h>
#include "cJSON.h"

#include "DeviceBase.h"
#include "Sensor.h"
#include "DeviceConfig.h"
#include "../Logger/Logger.h"
#include "../HashLib/HashLib.h"
#include "../EventEndpoint/EndpointClient/EndpointClient.h"

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
	void AddServerEndpoint(std::string server, uint port);
	
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
	bool init = false;
	EndpointClient *endpointClient = NULL;
};