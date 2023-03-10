#pragma once

#include <sstream>
#include <string>
#include <vector>
#include "udp_discovery_peer.hpp"
#include "udp_discovery_protocol.hpp"
#include "../Logger/Logger.h"
#include "Capabilities.h"
#include "Peer.h"

class ZeroConf
{
public:
	static ZeroConf *GetInstance();
	void SetupPeer(Capabilities caps, unsigned long appId = 8675309);
	void Start();
	std::vector<Peer> DiscoverPeers();
		
private:
	ZeroConf();
	static ZeroConf *instance;
	Logger *log;
	Capabilities caps;
	std::string capsString;
	unsigned long applicationID;
	udpdiscovery::Peer *udpPeer;
};