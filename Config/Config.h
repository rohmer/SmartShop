#pragma once

#include <string>
#include <vector>

#include "cJSON/cJSON.h"

#include "LogConfig.h"

class Config
{
public:
	Config();
	bool LoadConfig();
	bool SaveConfig();
	
	
};