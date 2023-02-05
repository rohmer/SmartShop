#pragma once

#include <time.h>
#include <string>

#include "LogLevel.h"

class LogMsg
{
public:
	unsigned long ID;
	std::string Host;
	int Severity;
	std::string Message;
	time_t Timestamp;
};