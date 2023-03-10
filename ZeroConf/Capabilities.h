#pragma once

#include <string>
#include <vector>
#include <cjson/cJSON.h>
#include "../RaspUtils/CPUInfo.h"

class Capabilities
{
public:
	enum eCaps
	{
		CAP_SERVER,
		CAP_UI,
		CAP_CLIENT
	};
	
	Capabilities();
	void AddCap(eCaps Capability);
	bool HasCap(eCaps Capability);
	
	cJSON *ToJSON();
	static Capabilities FromJSON(cJSON *json);
	
	std::string GetHostname()
	{
		return hostname;
	}
	
	std::string GetHostID()
	{
		return hostID;
	}
	
	void SetHostname(std::string hostname)
	{
		this->hostname = hostname;
	}
	
	void SetHostID(std::string hostID)
	{
		this->hostID = hostID;
	}
	
private:
	std::vector<eCaps> capabilities;
	std::string hostname, hostID;
};