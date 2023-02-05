#pragma once

#include "../GPIODevice.h"

class SwitchDevice : public GPIODevice
{
public:
	SwitchDevice(std::string Name, std::string Descritpion, uint TriggerPin);
	
	bool GetSwitchValue();
	
};