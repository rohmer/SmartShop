#pragma once

#include "../RaspUtils/CPUInfo.h"
#include <string>

class DBDevice
{
public:
	std::string CPUID, Hostname;
	uint CPUCount;
	int DeviceType;
	bool isAuth=false;
};