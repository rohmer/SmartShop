#pragma once

#include <string>
#include <cJSON.h>
#include "JSONTools.h"
#include "../../Logger/Logger.h"
#include "../../RaspUtils/JSON.h"

class TPLink_Device
{
public:
	TPLink_Device(std::string ipAddr);
	bool Valid();

	static TPLink_Device Factory(cJSON *j);
	enum eTPLinkDeviceType
	{
		SmartPlug = 0,
		SmartSwitch = 1,
		SmartBulb = 2,
		SmartSwitchDimmer = 3,
		SmartLightStrip = 4,
		RangeExtender = 5,
		UNKNOWN = 99
	};

	std::string GetSWVersion() { return sw_ver; }
	std::string GetHWVersion() { return hw_ver; }
	std::string GetType() { return tpType; }
	std::string GetModel() { return model; }
	std::string GetDeviceName() { return devName; }
	std::string GetDeviceAlias() { return alias; }
	void SetAlias(std::string newAlias)
	{
		alias = newAlias;
	}
	std::string GetDeviceID() { return deviceID; }
	std::string GetHwID() { return hwID; }
	std::string GetOEMId() { return oemID; }
	std::string GetMACAddress() { return mac; }
	int GetErrorCode() { return errCode; }
	int GetRSSI() { return rssi; }
	float GetLatitude() { return latitude; }
	float GetLongitude() { return longitude; }
	bool GetIsUpdating() { return updating; }
	bool IsValid() { return isValid; }
	std::string GetIPAddress() { return ipAddr; }
	eTPLinkDeviceType GetDeviceType() { return deviceType; }

protected:
	virtual bool parseJSON(cJSON* j);

	std::string sw_ver, hw_ver, tpType, model, devName, alias,
		deviceID, hwID, oemID, mac, ipAddr;
	int errCode, rssi;
	float latitude, longitude;
	bool updating;

	bool isValid = false;
	Logger* log;
	eTPLinkDeviceType deviceType;

};
