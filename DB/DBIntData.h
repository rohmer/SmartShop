#pragma once
#include <string>

class DBIntData
{
public:
	unsigned long ID;
	unsigned long EventID;
	std::string Name;
	long Value, Max, Min;
};