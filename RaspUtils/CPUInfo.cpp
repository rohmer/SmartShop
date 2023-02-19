#include "CPUInfo.h"

std::string CPUInfo::cpuID = "";
int CPUInfo::cpuCount = -1;
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
		}
		if (strcasecmp("processor", key) == 0)
			procCount++;
	}
	fclose(fp);
	cpuCount = procCount;
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