#pragma once
#include <string>

class DBDeviceConfig
{
public:
    unsigned int ID;
    std::string Hostname, DeviceName, DeviceDescription, DeviceID, CPUID;
    uint DeviceBus, DeviceType;
};