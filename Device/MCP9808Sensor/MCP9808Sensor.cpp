#include "MCP9808Sensor.h"

MCP9808Sensor::MCP9808Sensor(
	std::string Name, 
	std::string Description,
	unsigned int PollingInterval,
	eI2CBus I2CBus,
	unsigned short I2CAddress)
	: I2CDevice(Name, Description, eDeviceType::SENSOR, I2CAddress, I2CBus, PollingInterval)
	, Sensor()
{
	config.AddConfigItem(DeviceConfigItem("I2C Bus", (int)I2CBus, true));
	config.AddConfigItem(DeviceConfigItem("I2C Address", (int)I2CAddress, true));
}

uint8_t MCP9808Sensor::GetResolution()
{
	return ReadByteData(MCP9808_REG_RESOLUTION);
}

bool MCP9808Sensor::SetResolution(uint8_t resolution)
{
	int v = WriteByteData(MCP9808_REG_RESOLUTION, resolution & 0x03);
	if (v < 0)
		return false;
	return true;
}

std::vector<SensorEvent> MCP9808Sensor::PollSensor()
{
	std::vector<SensorEvent> ret;
	SensorEvent evt(name);
	float tempC = NAN;
	uint16_t t = ReadWordData(MCP9808_REG_AMBIENT_TEMP);

	if (t != 0xFFFF) {
		tempC = t & 0x0FFF;
		tempC /= 16.0;
		if (t & 0x1000)
			tempC -= 256;

		tempC = tempC * 9.0 / 5.0 + 32;
	}
	
	float tempF = NAN;
	
	if (t != 0xFFFF) {
		tempF = t & 0x0FFF;
		tempF /= 16.0;
		if (t & 0x1000)
			tempF -= 256;

		tempF = tempF * 9.0 / 5.0 + 32;
	}
	
	evt.AddEventData(FloatData("TempF", tempF));
	evt.AddEventData(FloatData("TempC", tempC));
	
	ret.push_back(evt);
	return ret;
}

bool MCP9808Sensor::Sleep()
{
	int16_t conf_shutdown;
	uint16_t conf_register = ReadWordData(MCP9808_REG_CONFIG);
	conf_shutdown = conf_register | MCP9808_REG_CONFIG_SHUTDOWN;
	int v=WriteWordData(MCP9808_REG_CONFIG, conf_shutdown);
	if (v < 0)
		return false;
	return true;
}

bool MCP9808Sensor::Wake()
{
	int16_t conf_shutdown;
	uint16_t conf_register = ReadWordData(MCP9808_REG_CONFIG);
	conf_shutdown = conf_register & ~MCP9808_REG_CONFIG_SHUTDOWN;
	int v=WriteWordData(MCP9808_REG_CONFIG, conf_shutdown);
	if (v < 0)
		return false;
	return true;
}