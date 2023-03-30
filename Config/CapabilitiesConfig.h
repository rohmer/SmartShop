#pragma once

#include <string>
#include "../../Device/DeviceConfig.h"

class CapabilitiesConfig
{
public:
	CapabilitiesConfig();
	
	static std::string GetName()
	{
		return "Capabilties Config";
	}
	
	DeviceConfig dc;
};