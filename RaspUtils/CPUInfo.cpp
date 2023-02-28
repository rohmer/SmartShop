#include "CPUInfo.h"

std::string CPUInfo::cpuID = "";
int CPUInfo::cpuCount = -1;
EPIType CPUInfo::piType = EPIType::CLEAR;
std::string CPUInfo::hostname = "";

std::string CPUInfo::GetHostname()
{
	if (hostname.length() == 0)
	{
		char hostn[1024];
		gethostname(hostn, 1024);
		std::string host(hostn);
		hostname = host;
	}	
	return hostname;
}

std::string CPUInfo::GetCPUID()
{
	if (cpuID.size() > 0)
		return cpuID;
	parseCPUInfo();
	return cpuID;
}

int CPUInfo::GetCPUCount()
{
	if (cpuCount == -1)
		parseCPUInfo();
	return cpuCount;
}

EPIType CPUInfo::GetPIBoardType()
{
	if (piType == EPIType::CLEAR)
		parseCPUInfo();
	return piType;
}

void CPUInfo::parseCPUInfo()
{
	uint32_t serial = 0;

	FILE *fp = fopen("/proc/cpuinfo", "r");

	if (fp == NULL)
	{
		perror("/proc/cpuinfo");
		exit(EXIT_FAILURE);
	}

	char entry[80];

	int procCount = 0;
	
	while (fgets(entry, sizeof(entry), fp) != NULL)
	{
		char* saveptr = NULL;

		char *key = trimWhiteSpace(strtok_r(entry, ":", &saveptr));
		char *value = trimWhiteSpace(strtok_r(NULL, ":", &saveptr));
		
		if (strcasecmp("Serial", key) == 0)
		{
			cpuID = value;	
			std::transform(cpuID.begin(),
				cpuID.end(),
				cpuID.begin(),
				[](unsigned char c){ return std::toupper(c); });
		}
		if (strcasecmp("processor", key) == 0)
			procCount++;
		if (strcasecmp("Revision", key) == 0)
			parseModelInfo(value);
			
	}
	fclose(fp);
	cpuCount = procCount;
}

void CPUInfo::parseModelInfo(std::string revInfo)
{
	if (revInfo.compare("900021")==0 || revInfo.compare("900032")==0)
	{
		piType = EPIType::PI_1;		
	}
	if (revInfo.compare("9000c1") == 0)
	{
		piType = EPIType::PI_ZERO;		
	}
	if (revInfo.compare("9020e0") == 0)
	{
		piType = EPIType::PI_3;		
	}
	if (revInfo.compare("900061") == 0)
	{
		piType = EPIType::PI_CM1;		
	}
	if (revInfo.compare("a01040") == 0 || revInfo.compare("a01041") == 0 || revInfo.compare("a21041") == 0)
	{
		piType = EPIType::PI_2;		
	}	
	if (revInfo.compare("a02082") == 0 || 
		revInfo.compare("a020d3") == 0 ||
		revInfo.compare("a22082") == 0 ||
		revInfo.compare("a32082") == 0 ||
		revInfo.compare("a32082") == 0 ||
		revInfo.compare("a32082") == 0)
	{
		piType = EPIType::PI_3;
	}
	if (revInfo.compare("a020a0") == 0 || revInfo.compare("a220a0") == 0 || revInfo.compare("a02100") == 0)
	{
		piType = EPIType::PI_CM3;		
	}
	if (revInfo.compare("a03111") == 0 || 
		revInfo.compare("b03111") == 0 ||
		revInfo.compare("b03112") == 0 ||
		revInfo.compare("b03114") == 0 ||
		revInfo.compare("b03115") == 0 ||
		revInfo.compare("c03111") == 0 ||
		revInfo.compare("c03112") == 0 ||
		revInfo.compare("c03114") == 0 ||
		revInfo.compare("c03115") == 0 ||
		revInfo.compare("d03114") == 0 ||
		revInfo.compare("d03115") == 0)
	{
		piType = EPIType::PI_4;
	}
	
	if (revInfo.compare("c03130") == 0)
	{
		piType = EPIType::PI_400;		
	}
	if (revInfo.compare("a03140") == 0 || 
		revInfo.compare("b03140") == 0 ||
		revInfo.compare("c03140") == 0 ||
		revInfo.compare("d03140") == 0)
	{
		piType = EPIType::PI_CM4;
	}
	
	if (piType == EPIType::CLEAR)
		piType = EPIType::PI_UNKNOWN;
}

char *CPUInfo::trimWhiteSpace(char *string)
{
	if (string == NULL)
	{
		return NULL;
	}

	while (isspace(*string))
	{
		string++;
	}

	if (*string == '\0')
	{
		return string;
	}

	char *end = string;

	while (*end)
	{
		++end;
	}
	--end;

	while ((end > string) && isspace(*end))
	{
		end--;
	}

	*(end + 1) = 0;
	return string;
}