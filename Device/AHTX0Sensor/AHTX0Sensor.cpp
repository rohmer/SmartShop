#include "AHTX0Sensor.h"

AHTX0Sensor::AHTX0Sensor(
	std::string Name,
	std::string Description,
	unsigned int PollingInterval,
	eI2CBus I2CBus,
	unsigned short I2CAddress) :
	I2CDevice(Name,Description,eDeviceType::SENSOR,I2CAddress,I2CBus, PollingInterval),
	Sensor()
{
	config.AddConfigItem(DeviceConfigItem("I2C Bus", (int)I2CBus, 0,2,true));
	config.AddConfigItem(DeviceConfigItem("I2C Address", (int)I2CAddress, 0,254,true));	
}

bool AHTX0Sensor::init()
{
	if (!WriteByte(AHTX0_CMD_SOFTRESET))
		return false;
	gpioDelay(20);
	if (!WriteByte(AHTX0_CMD_CALIBRATE))
		return false;
	if (!WriteByte(0x08))
		return false;
	if (!WriteByte(0x00))
		return false;
	int ctr = 0;
	while (ctr < 100 && (GetStatus() & AHTX0_STATUS_BUSY))
	{
		gpioDelay(10);
		ctr++;
	}
	if (ctr >= 100)
		return false;
	ctr = 0;
	while (!(GetStatus() & AHTX0_STATUS_CALIBRATED) && ctr < 100)
	{
		gpioDelay(10);
		ctr++;
	}
	if (ctr >= 100)
		return false;
	return true;
}

uint8_t AHTX0Sensor::GetStatus()
{
	uint8_t ret = ReadByte();
	return ret;
}

std::vector<SensorEvent> AHTX0Sensor::PollSensor()
{
	std::vector<SensorEvent> ret;
	if (!isInit)
	{
		if (!init())
		{
			return ret;
		}
	}
	if (!WriteByte(AHTX0_CMD_TRIGGER))
		return ret;
	if (!WriteByte(0x33))
		return ret;
	if (!WriteByte(0))
		return ret;
	int ctr = 0;
	while ((GetStatus() & AHTX0_STATUS_BUSY) && ctr < 100)
	{
		gpioDelay(10);
		ctr++;
	}
	if (ctr >= 100)
		return ret;
	
	std::vector<uint8_t> payload = ReadBytes(6);
	if (payload.size() < 6)
		return ret;
	uint32_t h = payload[1];
	h <<= 8;
	h |= payload[2];
	h <<= 4;
	h |= payload[3] >> 4;
	float humidity = ((float)h * 100) / 0x100000;
	
	uint32_t tdata = payload[3] & 0x0F;
	tdata <<= 8;
	tdata |= payload[4];
	tdata <<= 8;
	tdata |= payload[5];
	float tC  = ((float)tdata * 200 / 0x100000) - 50;
	float tF = tC * 1.8f + 32.0f;
	
	SensorEvent se(name);
	se.AddEventData(FloatData("RelativeHumidity", humidity));
	se.AddEventData(FloatData("TempC", tC));
	se.AddEventData(FloatData("TempF", tF));
	ret.push_back(se);
	return ret;
	
}

// the class factories
extern "C" DeviceBase* create() 
{
	AHTX0Sensor *obj = new AHTX0Sensor();
	return ((DeviceBase *)obj);
}

extern "C" void destroy(AHTX0Sensor * p) 
{
	delete p;
}