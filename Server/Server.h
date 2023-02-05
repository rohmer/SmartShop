#pragma once

#include "Logger.h"
#include "../RESTServer/RESTServer.h"
#include "LogEndpoint.h"
#include "RegisterEndpoint.h"
#include "../UI/WindowManager.h"
#include "../Device/DeviceManager.h"
#include "EventEndpoint.h"
#include "../ZeroConf/ZeroConf.h"
#include "../ZeroConf/Capabilities.h"
#include "Settings.h"

class Server
{
public:
	Server();
	
	bool Init();
	
private:
	Logger *log;
	RESTServer *restServer;
	DeviceManager *deviceManager;
};