#pragma once

#include <string>

class DBEventData
{
public:
	unsigned long ID;
	std::string SensorName;
	std::string Hostname;
	unsigned long EventTime;
	std::string HostID;
	unsigned long EventGroup;
};