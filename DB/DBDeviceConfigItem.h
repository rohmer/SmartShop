#pragma once

#include <string>

class DBDeviceConfigItem
{
public:
    unsigned int ID;
    std::string Name, Value, DeviceID, hostID, Max, Min, Step;
    bool ReadOnly;
    unsigned int DataType;
	
};