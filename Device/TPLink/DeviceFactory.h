#pragma once
#include "TPLink_Device.h"
#include "TPLink_Switch.h"
#include "TPLink_DimmerSwitch.h"
#include "TPLink_LightStrip.h"
#include "TPLink_Bulb.h"

class DeviceFactory
{
public:
	static std::shared_ptr<TPLink_Device> CreateDevice(cJSON* j, std::string ipAddr);

};

