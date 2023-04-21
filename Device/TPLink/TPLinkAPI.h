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
#include "../../Logger/Logger.h"
#include <thread>
#include "TPLink_Device.h"
#include "DeviceFactory.h"

class TPLinkAPI
{
public:
    TPLinkAPI() {};
    std::vector<std::shared_ptr<TPLink_Device>> Discovery(uint timeout = 30);
	bool SetAlias(std::string host, std::string alias);
	bool SetAlias(TPLink_Device host, std::string alias);
	bool SetBrightness(std::string host, int brightness);
	bool SetBrightness(TPLink_Device host, int brightness);
	bool RefreshItem(std::shared_ptr<TPLink_Device> &host);
	bool TurnOn(std::shared_ptr<TPLink_Device> host);
	bool TurnOn(std::string host);
	bool TurnOff(std::shared_ptr<TPLink_Device> host);
	bool TurnOff(std::string host);
	bool SetHSV(std::string host, int hue, int saturation, int brightness);
	bool SetHSV(std::shared_ptr<TPLink_Device> host, int hue, int saturation, int brightness);
	
	bool IsDimmable(std::shared_ptr<TPLink_Device> host);
	bool IsColor(std::shared_ptr<TPLink_Device> host);
	bool IsVariableColorTemp(std::shared_ptr<TPLink_Device> host);
	bool IsOn(std::shared_ptr<TPLink_Device> host);
	bool GetHSV(std::shared_ptr<TPLink_Device> host, int &h, int &s, int &v);
	bool GetColorTemp(std::shared_ptr<TPLink_Device> host, int &colorTemp);
	
private:
     union
    {
        uint32_t integer;
        uint8_t byte[4];
    } int32bit;

	uint8_t *encode(size_t *outputLength, const char *message, bool addHeader=true);
	bool encrypt(uint8_t *d, const uint8_t *s, size_t len);
	bool decrypt(uint8_t *d, const uint8_t *s, size_t len);
	uint8_t *decode(const uint8_t *s, size_t len);
	
	std::shared_ptr<TPLink_Device> parseResponse(std::string response, std::string ipAddr);
	std::string sendCommand(uint8_t *cmd, size_t cmdLen, std::string host);
};
