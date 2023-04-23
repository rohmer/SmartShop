#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "DeviceBase.h"
#include "dlclass.hpp"
#include "../Logger/Logger.h"

class DevicePluginManager
{
public:
	static DevicePluginManager *GetInstance();
	void LoadPlugins();
	
	std::shared_ptr<DeviceBase> DeviceFactory(std::string name);

	std::map<std::string, DLClass<DeviceBase> *> GetLoadedDevices();

private:
	static DevicePluginManager *instance;
	DevicePluginManager();
	
	std::map<std::string, DLClass<DeviceBase>*> loadedDevices;
	Logger *log;
};