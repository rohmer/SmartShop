#pragma once

#include <string>
#include <vector>

#include "sigar.h"

#include "../Logger/Logger.h"
#include "../RaspUtils/CPUInfo.h"
#include "CPUStats.h"
#include "FileSystemStats.h"
#include "ProcessTableStats.h"
#include "RAMStats.h"
#include "SwapStats.h"

struct sTelemetryReturn
{
public:
	time_t timestamp;
	SwapStats swap;
	std::vector<FileSystemStats> fileSystems;
	RAMStats memory;
	std::vector<ProcessTableStats> processes;
	CPUStats cpu;
};

class Telemetry
{
public:
	static sTelemetryReturn GetTelemetryStats(int maxFilesystems = -1, int maxProcesses = -1);

};