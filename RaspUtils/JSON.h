#pragma once

#include <string>
#include <cjson/cJSON.h>

class JSON
{
public:
	static std::string Print(const cJSON *json);
};