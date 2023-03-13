#pragma once

#include <string>
#include <thread>

#include "Settings.h"
#include "Configuration.h"
#include "DeviceManager.h"
#include "ConfigEndpoint.h"

#include "../Logger/Logger.h"
#include "../DeviceRegistration/HostRegistration.h"
#include "../DeviceRegistration/RegClient.h"

#include "Discovery.h"
#include "TelemetryAgent/TelemetryAgent.h"
#include "RESTServer.h"

class Client
{
public:
	Client();
	void Run();
	~Client();
	
private:
	DeviceManager *dm;
	Logger *log;
	ZeroConf *zeroConf;
	bool shutdown;
	Discovery *discovery;
	RESTServer *restServer; 
};