#pragma once

#include <string>
#include <vector>
#include <cjson/cJSON.h>

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
	
private:
	std::vector<eCaps> capabilities;
};