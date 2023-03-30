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
#include "../../EventEndpoint/EventEndpoint.h"
#include "../../LogEndpoint/LogEndpoint.h"
#include "../../DeviceRegistration/RegistrationEndpoint.h"

class Init
{
public:
	static bool InitServer();
	
private:
	static bool isInit;
	static Config *config;
};