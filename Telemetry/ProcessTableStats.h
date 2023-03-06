#pragma once

#include <string>

struct ProcessTableStats
{
public:
	std::string name, state;
	int pid;
	long size, resident, userTime, sysTime, totalTime, threads;
};