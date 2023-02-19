#pragma once
#include <string>

class DBDeviceConfig
{
public:
    unsigned int ID;
    std::string Hostname, DeviceName, DeviceDescription, DeviceID;
    uint DeviceBus, DeviceType;
};