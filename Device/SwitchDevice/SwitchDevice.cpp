#include "SwitchDevice.h"

SwitchDevice::SwitchDevice(std::string Name, std::string Description, uint TriggerPin)
	: GPIODevice(Name, Description, eDeviceType::GENERIC, GPIOPinDef(TriggerPin, GPIOPinDef::PIN_INPUT))
{
}

bool SwitchDevice::GetSwitchValue()
{
	return GetValue();
}