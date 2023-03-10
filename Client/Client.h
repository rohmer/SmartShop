#pragma once

#include <string>
#include <thread>

#include "Settings.h"
#include "Configuration.h"
#include "DeviceManager.h"

#include "../Logger/Logger.h"
#include "../DeviceRegistration/HostRegistration.h"
#include "../DeviceRegistration/RegClient.h"

class Client
{
public:
	Client();
	void Run();
	
private:
	DeviceManager *dm;
	Logger *log;
	ZeroConf *zeroConf;
	bool shutdown;
	std::vector<std::string> discoveredServers, discoveredClients;
		
	std::thread *discoveryThread;
	void discoveryLoop();
	
};