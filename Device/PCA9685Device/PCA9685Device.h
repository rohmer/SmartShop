#pragma once

#include <string>

#include "Defines.h"
#include "../../Logger/Logger.h"
#include "../I2CDevice.h"

class PCA9685Device : public I2CDevice
{
public:
	PCA9685Device(std::string Name = "PCA9685 Servo Driver", std::string Description = "PCA9685 16 Channel Servo Driver", eI2CBus I2CBus=eI2CBus::BUS_0, unsigned int I2CAddr=0x40);
	
	bool SetPWMFreq(float Frequency);
	bool SetExtClock(uint8_t Prescale);
	bool Sleep();
	bool Wake();
	bool SetOutputMode(bool TotemPole);
	uint8_t GetPWM(uint8_t num);
	bool SetPWM(uint8_t num, uint16_t on, uint16_t off);
	void SetPin(uint8_t num, uint16_t val, bool invert = false);
	void SetOscillatorFreq(uint32_t Frequency);
	uint8_t ReadPrescale();

private:
	Logger *log;
	uint32_t oscillator_freq;
};