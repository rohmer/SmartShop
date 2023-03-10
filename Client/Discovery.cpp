#include "Discovery.h"

Discovery::Discovery() :
	zeroConfig(ZeroConf::GetInstance())
{
	shutdown = false;
	discoveryThread = new std::thread([this]{discoveryLoop(); });
}

Discovery::~Discovery()
{
	shutdown = true;
	discoveryThread->join();
}

void Discovery::discoveryLoop()
{
	while (!shutdown)
	{
		std::vector<Peer> peers=zeroConfig->DiscoverPeers();
		for (std::vector<Peer>::iterator it = peers.begin();
			it != peers.end();
			++it)
		{
			Capabilities caps = it->GetCapabilities();
		
			bool exists = false;
			for (std::map<std::string, Capabilities>::iterator nit = foundIDs.begin(); nit != foundIDs.end(); ++nit)
				if (std::strcmp(nit->second.GetHostname().c_str(), caps.GetHostname().c_str()) == 0)
				{
					exists = true;
					nit = foundIDs.end();
				}
			if (!exists)
				foundIDs.emplace(caps.GetHostID(), caps);
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(30));
	}
}