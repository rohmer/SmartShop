#pragma once

#include <string>
#include <vector>

#include "../Sensor.h"
#include "../I2CDevice.h"
#include "../../Logger/Logger.h"

extern "C" DeviceBase *Factory();

class PM25AQISensor : public I2CDevice, public Sensor
{
public:
    PM25AQISensor(
		std::string Name = "PM25AQI", 
		std::string Description = "PM25AQI i2c air quality sensor", 
		unsigned int PollingInterval = 20, 
		eI2CBus i2cBus = eI2CBus::BUS_0);

	std::vector<SensorEvent> PollSensor() override;
	
private:

};