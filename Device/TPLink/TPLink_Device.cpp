#include "TPLink_Device.h"

TPLink_Device::TPLink_Device(std::string ipAddr) :
	log(Logger::GetInstance()),
	ipAddr(ipAddr)
{
}

bool TPLink_Device::Valid()
{
	return isValid;
}

bool TPLink_Device::parseJSON(cJSON *j)
{
	sw_ver = JSONTools::JSONGetString(j, "sw_ver");
	hw_ver = JSONTools::JSONGetString(j, "hw_ver");
	tpType = JSONTools::JSONGetString(j, "type");
	model = JSONTools::JSONGetString(j, "model");
	devName = JSONTools::JSONGetString(j, "dev_name");
	deviceID = JSONTools::JSONGetString(j, "deviceId");
	alias = JSONTools::JSONGetString(j, "alias");
	hwID = JSONTools::JSONGetString(j, "hwId");
	oemID = JSONTools::JSONGetString(j, "oemID");
	mac = JSONTools::JSONGetString(j, "mac");
	errCode = JSONTools::JSONGetInt(j, "err_code");
	rssi = JSONTools::JSONGetInt(j, "rssi");
	updating = JSONTools::JSONGetBool(j, "updating");
	latitude = JSONTools::JSONGetFloat(j, "latitude");
	longitude = JSONTools::JSONGetFloat(j, "longitude");
	
	if (tpType.length() > 0 && deviceID.length() > 0 && hwID.length() > 0 && oemID.length() > 0)
		return true;
}

