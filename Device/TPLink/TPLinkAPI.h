#pragma once

#include <inttypes.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <functional>
#include <thread>
#include <arpa/inet.h>

#include <cJSON.h>
#include "TPLinkDevice.h"

enum eTPLinkDeviceType
{
    SmartPlug = 0,
    SmartSwitch = 1,
    SmartBulb = 2,
    SmartLightStrip = 3
};

struct sTPLinkIOTDevice
{
public:
    sTPLinkIOTDevice(std::string IPAddress, eTPLinkDeviceType deviceType)
        : IPAddress(IPAddress)
        , DeviceType(deviceType)
    {
    }
    std::string IPAddress;
    eTPLinkDeviceType DeviceType;
};

class TPLinkAPI
{
public:
    TPLinkAPI() {};
    std::vector<sTPLinkIOTDevice> Discovery(uint timeout = 30);

private:
     union
    {
        uint32_t integer;
        uint8_t byte[4];
    } int32bit;

    std::string encrypt(std::string input);
    std::string decrypt(std::string input);
};
