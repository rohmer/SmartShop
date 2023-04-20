#pragma once

#include <string>

#include <cJSON.h>

class JSONTools
{
public:
	static std::string JSONGetString(cJSON* jsonObj, std::string name);
	static int JSONGetInt(cJSON* jsonObj, std::string name);
	static bool JSONGetBool(cJSON* jsonObj, std::string name);
	static float JSONGetFloat(cJSON* jsonObj, std::string name);
	static time_t JSONGetTime(cJSON* jsonObj, std::string name);
};