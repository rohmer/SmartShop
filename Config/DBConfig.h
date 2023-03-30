#pragma once

#include <string>
#include "../../Device/DeviceConfig.h"

class DBConfig
{
public:
	DBConfig();
	
	static std::string GetName()
	{
		return "Database Config";
	}
	
	DeviceConfig dc;
};
