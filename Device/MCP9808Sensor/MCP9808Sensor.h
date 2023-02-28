#pragma once

#include <string>
#include <vector>

#include "../Sensor.h"
#include "../I2CDevice.h"
#include "../../Logger/Logger.h"
#include "Defines.h"

class MCP9808Sensor : public I2CDevice, public Sensor
{
	MCP9808Sensor(
		std::string Name="MCP9808", 
		std::string Description="MCP9808 Temperature",
		unsigned int PollingInterval=300,
		eI2CBus I2CBus=eI2CBus::BUS_0,
		unsigned short I2CAddress=0x18);
	
	std::vector<SensorEvent> PollSensor() override;
	uint8_t GetResolution();
	bool SetResolution(uint8_t Resolution);
	bool Sleep();
	bool Wake();
	
};