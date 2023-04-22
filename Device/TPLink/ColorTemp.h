#pragma once

#include <map>
#include <string>
#include "TPLink_Device.h"

class ColorTemp
{
public:
	static bool GetColorTempRange(std::shared_ptr<TPLink_Device> host, 
		int &min, int &max);

private:
	static std::map<std::string, std::pair<int, int>> temps;
	static void updateMaps();
};
