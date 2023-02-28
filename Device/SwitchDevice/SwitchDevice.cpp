#include "SwitchDevice.h"

SwitchDevice::SwitchDevice(std::string Name, std::string Description, uint TriggerPin)
	: GPIODevice(Name, Description, eDeviceType::GENERIC, GPIOPinDef(TriggerPin, GPIOPinDef::PIN_INPUT))
{
	config.AddConfigItem(DeviceConfigItem("triggerPin", (int)TriggerPin, false));
}

bool SwitchDevice::GetSwitchValue()
{
	return GetValue();
}