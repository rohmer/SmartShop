#pragma once

#include <string>
#include "../../Device/DeviceConfig.h"
#include "../../RaspUtils/CPUInfo.h"
class RESTConfig
{
public:
	RESTConfig();
	
	static std::string GetName()
	{
		return "REST Config";
	}
	
	DeviceConfig dc;
};
