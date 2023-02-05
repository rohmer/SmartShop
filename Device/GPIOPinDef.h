#pragma once

#include <string>

class GPIOPinDef
{
public:
	enum ePinMode
	{
		PIN_INPUT  = 0,
		PIN_OUTPUT = 1,
		PIN_ALT0   = 4,
		PIN_ALT1   = 5,
		PIN_ALT2   = 6,
		PIN_ALT3   = 7,
		PIN_ALT4   = 3,
		PIN_ALT5   = 2
	};
	
	enum ePullupDown
	{
		PIN_PUD_OFF  = 0,
		PIN_PUD_DOWN = 1,
		PIN_PUD_UP   = 2	
	};
	
unsigned short Pin;
	ePinMode PinMode;
	ePullupDown PullupDown;
	
	GPIOPinDef(unsigned short PinNumber, ePinMode Mode, ePullupDown PullupOrDown=PIN_PUD_OFF)
		: Pin(PinNumber)
		, PinMode(Mode)
		, PullupDown(PullupOrDown)
	{
	}
};