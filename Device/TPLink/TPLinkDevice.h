#pragma once

#include <string>
#include <cJSON.h>

class TPLinkDevice
{
public:
	TPLinkDevice(cJSON* discovery);

	std::string swVersion;
	float HWVersion;
	std::string stringType;
	std::string model;
	std::string deviceName;
	bool relayState;
	long onTime;
	std::string activeMode;
	std::string feature;
	bool updating;
	int rssi;
	bool ledOff;
	std::string alias;
	std::string deviceID;
	std::string hwID;
	std::string oemID;
	float lattitude, longitude;
	std::string macAddr;
	int errorCode;
};
