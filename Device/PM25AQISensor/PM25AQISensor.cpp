#include "PM25AQISensor.h"

PM25AQISensor::PM25AQISensor(
	std::string Name, 
	std::string Description,
	unsigned int PollingInterval, 
	eI2CBus i2cBus)
	: I2CDevice(Name, Description, eDeviceType::SENSOR, 0x12, i2cBus, PollingInterval)
	, Sensor()
{
	config.AddConfigItem(DeviceConfigItem("I2CBus", (int)i2cBus, false));
	config.AddConfigItem(DeviceConfigItem("I2CAddr", (int)0x12, false));
}

std::vector<SensorEvent> PM25AQISensor::PollSensor()
{
	std::vector<SensorEvent> ret;
	std::string read = ReadDevice(32);
	if (read[0] != 0x42)
	{
		log->LogC("Invalid data from PM25AQI");
		return ret;
	}
	uint16_t sum = 0;
	
	for (uint8_t i = 0; i < 30; i++) {
		sum += read[i];
	}
	
	// The data comes in endian'd, this solves it so it works on all platforms
	uint16_t buffer_u16[15];
	for (uint8_t i = 0; i < 15; i++) {
		buffer_u16[i] = read[2 + i * 2 + 1];
		buffer_u16[i] += (read[2 + i * 2] << 8);
	}
	
	SensorEvent se1 = SensorEvent("PM25AQI");
	se1.AddEventData(IntData("PM10Standard", buffer_u16[1]));
	se1.AddEventData(IntData("PM25Standard", buffer_u16[2]));
	se1.AddEventData(IntData("PM100Standard", buffer_u16[3]));
	se1.AddEventData(IntData("PM10Env", buffer_u16[4]));
	se1.AddEventData(IntData("PM25Env", buffer_u16[5]));
	se1.AddEventData(IntData("PM100Env", buffer_u16[6]));
	se1.AddEventData(IntData("Particles03", buffer_u16[7]));
	se1.AddEventData(IntData("Particles05", buffer_u16[8]));
	se1.AddEventData(IntData("Particles10", buffer_u16[9]));
	se1.AddEventData(IntData("Particles25", buffer_u16[10]));
	se1.AddEventData(IntData("Particles50", buffer_u16[11]));
	se1.AddEventData(IntData("Particles100", buffer_u16[12]));
	
	if (sum != buffer_u16[14])
	{
		log->LogW("Checksum Error");
	}
	
	ret.push_back(se1);
	return ret;
}


	