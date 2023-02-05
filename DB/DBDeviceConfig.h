#pragma once
#include <string>

class DBDeviceConfig
{
public:
    unsigned int ID;
    std::string Hostname, DeviceName, DeviceDescription;
    uint DeviceBus, DeviceType;
};