#include "PCA9685Device.h"

PCA9685Device::PCA9685Device(std::string Name, std::string Description, eI2CBus I2CBus, unsigned int I2CAddr)
	: I2CDevice(Name, Description, eDeviceType::GENERIC, I2CAddr, I2CBus),
	log(Logger::GetInstance()),
	oscillator_freq(FREQUENCY_OSCILLATOR)
{
	config.AddConfigItem(DeviceConfigItem("I2C BUS", (int)I2CBus,0, 2,true));
	config.AddConfigItem(DeviceConfigItem("Frequency", (long)FREQUENCY_OSCILLATOR,std::numeric_limits<long>::min(),std::numeric_limits<long>::max(), true));
}

void PCA9685Device::SetOscillatorFreq(uint32_t Frequency)
{
	oscillator_freq = Frequency;
}

bool PCA9685Device::SetPWMFreq(float Frequency)
{
	if (Frequency < 1)
		Frequency = 1;
	if (Frequency > 3500)
		Frequency = 3500;
	float prescaleval = ((oscillator_freq / (Frequency * 4096.0)) + 0.5) - 1;
	if (prescaleval < PCA9685_PRESCALE_MIN)
		prescaleval = PCA9685_PRESCALE_MIN;
	if (prescaleval > PCA9685_PRESCALE_MAX)
		prescaleval = PCA9685_PRESCALE_MAX;
	uint8_t prescale = (uint8_t)prescaleval;
	
	uint8_t oldmode = ReadByteData(PCA9685_MODE1);
	uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
	if(!WriteByteData(PCA9685_MODE1, newmode))			// go to sleep
		return false; 
	if(!WriteByteData(PCA9685_PRESCALE, prescale))		// set the prescaler
		return false; 
	if(!WriteByteData(PCA9685_MODE1, oldmode))
		return false;
	gpioDelay(5);
	if(!WriteByteData(PCA9685_MODE1, oldmode | MODE1_RESTART | MODE1_AI))
		return false;

	return true;
}

bool PCA9685Device::SetExtClock(uint8_t Prescale)
{
	uint8_t oldmode = ReadByteData(PCA9685_MODE1);
	uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
	if(!WriteByteData(PCA9685_MODE1, newmode)) // go to sleep, turn off internal oscillator
		return false;
	// This sets both the SLEEP and EXTCLK bits of the MODE1 register to switch to
	// use the external clock.
	if(!WriteByteData(PCA9685_MODE1, (newmode |= MODE1_EXTCLK)))
		return false;

	if(!WriteByteData(PCA9685_PRESCALE, Prescale)) // set the prescaler
		return false;
	gpioDelay(5);
	// clear the SLEEP bit to start
	if(!WriteByteData(PCA9685_MODE1, (newmode & ~MODE1_SLEEP) | MODE1_RESTART | MODE1_AI))
		return false;

	return true;
}

bool PCA9685Device::Sleep()
{
	uint8_t awake = ReadByteData(PCA9685_MODE1);
	uint8_t sleep = awake | MODE1_SLEEP; // set sleep bit high
	if(!WriteByteData(PCA9685_MODE1, sleep))
		return false;
	gpioDelay(5); // wait until cycle ends for sleep to be active
	return true;
}

bool PCA9685Device::Wake()
{
	uint8_t sleep = ReadByteData(PCA9685_MODE1);
	uint8_t wakeup = sleep & ~MODE1_SLEEP; // set sleep bit low
	if(!WriteByteData(PCA9685_MODE1, wakeup))
		return false;
	return true;
}

bool PCA9685Device::SetOutputMode(bool TotemPole)
{
	uint8_t oldmode = ReadByteData(PCA9685_MODE2);
	uint8_t newmode;
	if (TotemPole) 
	{
		newmode = oldmode | MODE2_OUTDRV;
	}
	else {
		newmode = oldmode & ~MODE2_OUTDRV;
	}
	if(!(PCA9685_MODE2, newmode))
		return false;
	return true;
}

void PCA9685Device::SetPin(uint8_t num, uint16_t val, bool invert)
{
	val = std::min(val, (uint16_t)4095);
	if (invert) {
		if (val == 0) {
			// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 4095) {
			// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, 4095 - val);
		}
	}
	else {
		if (val == 4095) {
			// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 0) {
			// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, val);
		}
	}
}

uint8_t PCA9685Device::GetPWM(uint8_t num)
{
	std::string v = ReadI2CBlockData(PCA9685_LED0_ON_L + 4 * num, (int)4);
	return ReadByte();
}

bool PCA9685Device::SetPWM(uint8_t num, uint16_t on, uint16_t off)
{
	if (!WriteByte(PCA9685_LED0_ON_L + 4 * num))
	{
		log->LogC("Failed to SetPWM");
		return false;
	}
	if (!WriteByte(on))
	{
		log->LogC("Failed to SetPWM");
		return false;
	}

	if (!WriteByte(on >> 8))
	{
		log->LogC("Failed to SetPWM");
		return false;
	}
	if (!WriteByte(off))
	{
		log->LogC("Failed to SetPWM");
		return false;
	}
	if (!WriteByte(off >> 8))
	{
		log->LogC("Failed to SetPWM");
		return false;
	}
	return true;
}

uint8_t PCA9685Device::ReadPrescale()
{
	return ReadByteData(PCA9685_PRESCALE);
}

// the class factories
extern "C" DeviceBase* create() 
{
	PCA9685Device *obj = new PCA9685Device();
	return ((DeviceBase *)obj);
}

extern "C" void destroy(PCA9685Device * p) 
{
	delete p;
}