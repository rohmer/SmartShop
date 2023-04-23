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

#include "DeviceConfig.h"
#include "../Logger/Logger.h"
#include "../HashLib/HashLib.h"
#include "../EventEndpoint/EndpointClient/EndpointClient.h"
#include "DeviceBase.h"
#include "Sensor.h"
#include "pigpio.h"
#include "DevicePluginManager.h"

class DeviceManager
{
public:
	static DeviceManager *GetInstance();
	~DeviceManager();	
	
	std::vector<std::shared_ptr<DeviceBase>> GetDeviceByType(eDeviceType deviceType);
	std::shared_ptr<DeviceBase> GetDeviceByName(std::string name);
	std::vector<std::shared_ptr<DeviceBase>> GetDeviceByBus(eDeviceBus deviceBus);
	
	std::vector<std::string> GetServerEndpoints();
	
	std::vector<std::shared_ptr<DeviceBase>> GetAllDevices();
	
	void AddServerEndpoint(std::string server, uint port);
	
	std::thread *updateThread;
	
	bool AddDevice(std::string DeviceName);
	
private:
	static DeviceManager *instance;
	DeviceManager();
	void updateLoop();
	
	
	Logger *log;
	Bosma::Scheduler *scheduler;
	
	std::vector<std::string> serverEndpoints;
	std::map<eDeviceBus, std::vector<std::shared_ptr<DeviceBase>>> deviceByBus;
	std::map<eDeviceType, std::vector<std::shared_ptr<DeviceBase>>> deviceByType;
	std::map<std::string, std::shared_ptr<DeviceBase>> deviceByName;
	std::map<std::string, DeviceConfig> deviceConfigs;
	std::vector<std::shared_ptr<DeviceBase>> devices;
	void scheduleSensor(std::shared_ptr<Sensor> sensor);
	void rescheduleSensors();
	
	bool storeConfig();
	bool loadConfig();
	bool shutdown = false;
	bool init = false;
	EndpointClient *endpointClient = NULL;
	DevicePluginManager *pluginManager = NULL;
};