#pragma once

#include "../GPIODevice.h"

extern "C" DeviceBase *Factory();
class SwitchDevice : public GPIODevice
{
public:
	SwitchDevice();
	SwitchDevice(std::string Name, std::string Descritpion, uint TriggerPin);
	
	bool GetSwitchValue();
	
};