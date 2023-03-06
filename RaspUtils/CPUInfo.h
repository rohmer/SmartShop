#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum EPIType
{
	PI_1,
	PI_2,
	PI_CM1,
	PI_3,
	PI_CM3,
	PI_ZERO,
	PI_ZERO_2,
	PI_4,
	PI_CM4,
	PI_400,
	PI_UNKNOWN,
	CLEAR
};

class CPUInfo
{
public:
	static std::string GetCPUID();
	static int GetCPUCount();
	static EPIType GetPIBoardType();
	static std::string GetHostname();
	static float GetTempC();
	
private:
	static std::string hostname;
	static void parseCPUInfo();
	static void parseModelInfo(std::string revInfo);
	
	static std::string cpuID;
	static char *trimWhiteSpace(char *string);
	static int cpuCount;
	static EPIType piType;
};