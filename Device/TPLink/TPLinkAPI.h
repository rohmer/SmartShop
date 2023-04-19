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
#include "../../Logger/Logger.h"
#include <thread>

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

	uint8_t *encode(size_t *outputLength, const char *message);
	bool encrypt(uint8_t *d, const uint8_t *s, size_t len);
	bool decrypt(uint8_t *d, const uint8_t *s, size_t len);
	uint8_t *decode(const uint8_t *s, size_t len);
	
	int send(int socketFD, std::string msg, const struct sockaddr *s);
		
};
