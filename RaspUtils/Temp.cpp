#include "Temp.h"

float Temp::CPUTempC()
{
	std::ifstream f("/sys/class/thermal/thermal_zone0/temp");
	if (f.is_open())
	{
		float temp;
		f >> temp;
		return temp / 1000;
	}
}