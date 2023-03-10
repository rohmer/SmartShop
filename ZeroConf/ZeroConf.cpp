#include "ZeroConf.h"
ZeroConf *ZeroConf::instance = NULL;

ZeroConf *ZeroConf::GetInstance()
{
	if (instance == NULL)
		instance = new ZeroConf();
	return instance;
}

ZeroConf::ZeroConf() 
{
	log = Logger::GetInstance();
}

void ZeroConf::SetupPeer(Capabilities caps, unsigned long appId)
{
	try
	{
		capsString = cJSON_Print(caps.ToJSON());
	}
	catch (const std::exception&e)
	{
		std::stringstream ss;
		ss << "Failed to generate capabilities: " << e.what();
		log->LogC(ss.str());
	}
	this->applicationID = appId;
}

void ZeroConf::Start()
{
	udpdiscovery::PeerParameters paras;
	paras.set_application_id(applicationID);
	paras.set_can_be_discovered(true);
	paras.set_can_discover(true);
	paras.set_port(6666);
	udpPeer = new udpdiscovery::Peer();
	udpPeer->Start(paras, capsString);
}

std::vector<Peer> ZeroConf::DiscoverPeers()
{
	std::list<udpdiscovery::DiscoveredPeer> peers = udpPeer->ListDiscovered();
	
	std::vector<Peer> ret;
	for (std::list<udpdiscovery::DiscoveredPeer>::iterator it = peers.begin(); it != peers.end(); ++it)
	{
		std::string ipAddr = udpdiscovery::IpPortToString(it->ip_port());
		unsigned int port = it->ip_port().port();
		unsigned long lastPacket = it->last_received_packet();
		Capabilities caps;
		try
		{
			cJSON *json = cJSON_Parse(it->user_data().c_str());
			caps = Capabilities::FromJSON(json);
		}
		catch (const std::exception &e)
		{
			std::stringstream ss;
			ss << "Failed to parse capabilities from: " << ipAddr << ", error: " << e.what();
			log->LogW(ss.str());
		}
		
		ret.push_back(Peer(caps, ipAddr, port, lastPacket));
	}
	return ret;
}