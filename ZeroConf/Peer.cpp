#include "Peer.h"

Peer::Peer(Capabilities caps, std::string ipAddr, unsigned int port, unsigned long lastPacket)
	: capabilities(caps)
	, ipAddr(ipAddr)
	, port(port)
	, lastReceivedPacket(lastPacket)
{
}

Capabilities Peer::GetCapabilities()
{
	return capabilities;
}

std::string Peer::GetIPAddr()
{
	return ipAddr;
}

unsigned int Peer::GetDiscoveryPort()
{
	return port;
}

unsigned long Peer::GetLastReceviedPacket()
{
	return lastReceivedPacket;
}