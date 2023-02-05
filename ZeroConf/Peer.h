#pragma once

#include "Capabilities.h"

class Peer
{
public:
	Peer(Capabilities caps, std::string ipAddr, unsigned int discoveryPort, unsigned long lastPacket);
	
	Capabilities GetCapabilities();
	
	std::string GetIPAddr();
	unsigned int GetDiscoveryPort();
	unsigned long GetLastReceviedPacket();
	
private:
	Capabilities capabilities;
	std::string ipAddr;
	unsigned int port;
	unsigned long lastReceivedPacket;
};