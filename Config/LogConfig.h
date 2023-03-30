#pragma once

#include <string>
#include "../../Device/DeviceConfig.h"

class LogConfig
{
public:
	LogConfig();

	static std::string GetName()
	{
		return "Logger Configuration";
	}
	
	DeviceConfig dc;
};