#include "GPIODevice.h"

GPIODevice::GPIODevice(std::string Name, std::string Description, eDeviceType Type)
	: DeviceBase(Name, Description, Type, eDeviceBus::GPIO)
{
}

GPIODevice::GPIODevice(std::string Name, std::string Description, eDeviceType Type, GPIOPinDef devicePin)
	: DeviceBase(Name, Description, Type, eDeviceBus::GPIO)	
{
	pins.push_back(devicePin);
}

GPIODevice::GPIODevice(std::string Name, std::string Description, eDeviceType Type, GPIOPinDef devicePin, DeviceConfig config)
	: DeviceBase(Name, Description, config, Type, eDeviceBus::GPIO) 	
{
	pins.push_back(devicePin);
}

GPIODevice::GPIODevice(std::string Name, std::string Description, eDeviceType Type, std::vector<GPIOPinDef> devicePins, DeviceConfig config) 
	: DeviceBase(Name, Description, config, Type, eDeviceBus::GPIO)	
{
	for (std::vector<GPIOPinDef>::iterator it = devicePins.begin(); it != devicePins.end(); ++it)
		pins.push_back(*it);
}

void GPIODevice::setupPins()
{
	for (std::vector<GPIOPinDef>::iterator it = pins.begin(); it != pins.end(); ++it)
	{
		int v = gpioSetMode(it->Pin, it->PinMode);
		if (v == 0)
		{
			v = gpioSetPullUpDown(it->Pin, it->PullupDown);			
		}
		if (v == PI_BAD_GPIO)
		{
			std::stringstream ss;
			ss << "Bad GPIO # on pin: " << it->Pin;			
			log->LogC(ss.str());
		}
		if (v == PI_BAD_MODE)
		{
			std::stringstream ss;
			ss << "Bad Mode # on pin: " << it->Pin << ", mode: " << it->PinMode;			
			log->LogC(ss.str());
		}
	}
}

bool GPIODevice::GetValue(uint Pin)
{
	bool pinValid = false, pinModeInput=false;
	for (std::vector<GPIOPinDef>::iterator it = pins.begin(); it != pins.end(); ++it)
		if (it->Pin == Pin)
		{
			pinValid = true;
			if (it->PinMode == GPIOPinDef::PIN_INPUT)
				pinModeInput = true;
		}
	if (pinValid == true && pinModeInput==true)
	{
		return gpioRead(Pin);
	}
	if (!pinValid)
	{
		std::stringstream ss;
		ss << "Pin (" << Pin << ") not registered to device (" << name << ")";
		log->LogC(ss.str());
	}
	if (!pinModeInput)
	{
		std::stringstream ss;
		ss << "Pin (" << Pin << ") not set to Input for GetValue";
		log->LogC(ss.str());
	}
	return false;
}

bool GPIODevice::GetValue()
{
	if (pins.size() == 0)
	{
		std::stringstream ss;
		ss << "No pins registered to device: " << name;
		log->LogC(ss.str());
		return false;
	}
	
	if (pins[0].PinMode != GPIOPinDef::PIN_INPUT)
	{
		std::stringstream ss;
		ss << "Pin (" << pins[0].Pin << ") not set to Input for GetValue";
		log->LogC(ss.str());
		return false;
	}
	return gpioRead(pins[0].Pin);
}

bool GPIODevice::SetValue(uint Pin, bool Value)
{
	bool pinValid = false, pinModeInput = false;
	for (std::vector<GPIOPinDef>::iterator it = pins.begin(); it != pins.end(); ++it)
		if (it->Pin == Pin)
		{
			pinValid = true;
			if (it->PinMode == GPIOPinDef::PIN_INPUT)
				pinModeInput = true;
		}
	if (pinValid == true && pinModeInput == true)
	{
		return gpioRead(Pin);
	}
	if (!pinValid)
	{
		std::stringstream ss;
		ss << "Pin (" << Pin << ") not registered to device (" << name << ")";
		log->LogC(ss.str());
	}
	if (!pinModeInput)
	{
		std::stringstream ss;
		ss << "Pin (" << Pin << ") not set to Output for SetValue";
		log->LogC(ss.str());
	}
	int v;
	if (Value)
		v=gpioWrite(Pin, PI_HIGH);
	else
		v=gpioWrite(Pin, PI_LOW);
	if (v == 0)
		return true;
	return false;
}

bool GPIODevice::SetValue(bool Value)
{
	if (pins.size() == 0)
	{
		std::stringstream ss;
		ss << "No pins registered to device: " << name;
		log->LogC(ss.str());
		return false;
	}
	
	if (pins[0].PinMode != GPIOPinDef::PIN_OUTPUT)
	{
		std::stringstream ss;
		ss << "Pin (" << pins[0].Pin << ") not set to Output for SetValue";
		log->LogC(ss.str());
		return false;
	}
	int v;
	if (Value)
		v = gpioWrite(pins[0].Pin, PI_HIGH);
	else
		v = gpioWrite(pins[0].Pin, PI_LOW);
	if (v == 0)
		return true;
	return false;
}

bool GPIODevice::AddPin(unsigned short PinNumber, GPIOPinDef::ePinMode PinMode, GPIOPinDef::ePullupDown PullupOrDown)
{
	for (std::vector<GPIOPinDef>::iterator it = pins.begin();
		it != pins.end();
		++it)
	{
		if (it->Pin == PinNumber)
		{
			std::stringstream ss;
			ss << "Pin(" << PinNumber << ") already defined as: " << PinMode << ", not reassinging";
			log->LogW(ss.str());
			return false;
		}
	}
	pins.push_back(GPIOPinDef(PinNumber, PinMode, PullupOrDown));
}