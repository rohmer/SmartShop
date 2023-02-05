#pragma once

#include <string>
#include <vector>

#include "pigpio.h"

#include "DeviceBase.h"
#include "DeviceConfig.h"
#include "GPIOPinDef.h"
#include "../Logger/Logger.h"

class GPIODevice : public DeviceBase
{
public:
	GPIODevice(std::string Name, std::string Description, eDeviceType Type, GPIOPinDef devicePin);
	GPIODevice(std::string Name, std::string Description, eDeviceType Type, GPIOPinDef devicePin, DeviceConfig config);
	
	GPIODevice(std::string Name, std::string Description, eDeviceType Type, std::vector<GPIOPinDef> devicePins, DeviceConfig config);

	bool GetValue(uint Pin);
	bool GetValue();
	
	bool SetValue(uint Pin, bool Value);
	bool SetValue(bool Value);
	
private:
	std::vector<GPIOPinDef> pins;
	
	void setupPins();	
};
