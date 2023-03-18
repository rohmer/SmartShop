#pragma once

#include <string>
#include "cJSON.h"

class JSON
{
public:
	static std::string Print(const cJSON *json);
};