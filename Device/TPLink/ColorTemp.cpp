#include "ColorTemp.h"
std::map<std::string, std::pair<int, int>> ColorTemp::temps;

bool ColorTemp::GetColorTempRange(std::shared_ptr<TPLink_Device> host, 
	int &min, int &max)
{
	if (temps.size() == 0)
	{
		updateMaps();
	}
	if (temps.count(host->GetModel()))
	{
		min = temps[host->GetModel()].first;
		max = temps[host->GetModel()].second;
		return true;
	}
	return false;
}

void ColorTemp::updateMaps()
{
	temps.emplace("LB130", std::pair<int, int>(2500, 9000));
	temps.emplace("LB120", std::pair<int, int>(2700, 6500));
	temps.emplace("LB230", std::pair<int, int>(2500, 9000));
	temps.emplace("KB130", std::pair<int, int>(2500, 9000));
	temps.emplace("KL130", std::pair<int, int>(2500, 9000));
	temps.emplace("KL125", std::pair<int, int>(2500, 6500));
	temps.emplace("KL135", std::pair<int, int>(2500, 6500));
	temps.emplace("KL120(EU)", std::pair<int, int>(2700, 6500));
	temps.emplace("KL120(US)", std::pair<int, int>(2700, 5000));
	temps.emplace("KL430", std::pair<int, int>(2500, 9000));
}