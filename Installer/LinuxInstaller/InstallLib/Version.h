#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <cJSON.h>
#include "../../../Logger/Logger.h"

struct Version
{
public:
	uint Major, Minor, BuildNumber;
	
	Version(uint major=0, uint minor=0, uint buildNum=0)
		: Major(major)
		, Minor(minor)
		, BuildNumber(buildNum)
	{
	}
	
	static Version FromFile(std::string file);
	bool ToFile(std::string file);
	cJSON *ToJSON();
	static Version FromJSON(cJSON *json);
	
	std::string ToString();
};