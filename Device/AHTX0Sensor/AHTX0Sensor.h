#pragma once

#include <string>
#include <vector>

#include "Defines.h"
#include "../../SensorEvent/SensorEvent.h"
#include "../I2CDevice.h"
#include "../Sensor.h"

class AHTX0Sensor : public I2CDevice, public Sensor
{
public:
	AHTX0Sensor(DeviceConfig deviceConfig,
		std::string Name="AHTX0Sensor", 
		std::string Description="AHT10/20 Temperature/Humidity Sensor",
		unsigned int PollingInterval=300,
		eI2CBus I2CBus=eI2CBus::BUS_0,
		unsigned short I2CAddress=AHTX0_I2CADDR_DEFAULT);
	
	std::vector<SensorEvent> PollSensor() override;
	uint8_t GetStatus();
	
private:
	bool init();
	bool isInit = false;
	
};