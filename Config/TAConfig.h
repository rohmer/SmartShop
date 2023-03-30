#pragma once

#include <string>
#include "../../Device/DeviceConfig.h"

class TAConfig
{
public:
	TAConfig();

	static std::string GetName()
	{
		return "Telemetry Agent";
	}
	
	DeviceConfig dc;
};