#pragma once

#include <string>
#include <fstream>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CPUInfo
{
public:
	static std::string GetCPUID();
	static int GetCPUCount();
	
private:
	static void parseCPUInfo();
	static std::string cpuID;
	static char *trimWhiteSpace(char *string);
	static int cpuCount;
};