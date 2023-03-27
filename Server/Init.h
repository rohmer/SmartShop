#pragma once

#include "Settings.h"
#include "Logger.h"
#include "../RESTServer/RESTServer.h"
#include "LogEndpoint.h"
#include "../UI/WindowManager.h"
#include "../Device/DeviceManager.h"
#include "../EventEndpoint/EventEndpoint.h"
#include "../ZeroConf/ZeroConf.h"
#include "../ZeroConf/Capabilities.h"
#include "../DeviceRegistration/RegistrationEndpoint.h"
#include "../Device/TelemetryAgent/TelemetryAgent.h"
#include "../DB/DB.h"
#include "../Config/Config.h"
#include "../Config/LogConfig.h"
#include "../Config/ServerConfig.h"

class Init
{
public:
	bool InitServer();
	
private:
	static bool isInit;
};