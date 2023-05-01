#include "SwitchDevice.h"

SwitchDevice::SwitchDevice(std::string Name, std::string Description, uint TriggerPin)
	: GPIODevice(Name, Description, eDeviceType::GENERIC, GPIOPinDef(TriggerPin, GPIOPinDef::PIN_INPUT))
{
	config.AddConfigItem(DeviceConfigItem("triggerPin", (int)TriggerPin, 0,55,false));
}

SwitchDevice::SwitchDevice()
	: GPIODevice("Switch Device", "Device for monitoring GPIO High/Low", eDeviceType::GENERIC)
{
}

bool SwitchDevice::GetSwitchValue()
{
	return GetValue();
}

// the class factories
extern "C" DeviceBase* create() 
{
	SwitchDevice *obj = new SwitchDevice();
	return ((DeviceBase *)obj);
}

extern "C" void destroy(SwitchDevice *p) 
{
	delete p;
}