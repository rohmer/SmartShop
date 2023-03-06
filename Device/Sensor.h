#pragma once
#include <string>
#include "DeviceConfig.h"
#include "../SensorEvent/SensorEvent.h"

class Sensor 
{
public:
	
	Sensor()
	{		
	}
	
	
	virtual std::vector<SensorEvent> PollSensor()
	{
	}		
		

};