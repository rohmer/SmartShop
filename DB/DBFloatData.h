#pragma once
#include <string>

class DBFloatData
{
public:
	unsigned long ID;
	unsigned long EventID;
	std::string Name;
	float Value, Max, Min;
};