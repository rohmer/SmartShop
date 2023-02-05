#pragma once

#include <string>

class DBDeviceConfigItem
{
public:
    unsigned int ID, DeviceID;
    std::string Name, Value;
    bool ReadOnly;
    unsigned int DataType;
};