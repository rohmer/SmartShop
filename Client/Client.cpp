#include "Client.h"


using namespace std;

Client::Client() :
	dm(DeviceManager::GetInstance())
{
	shutdown = false;
	log = Logger::GetInstance();
	log->Init(true);
	zeroConf = ZeroConf::GetInstance();
	Capabilities caps;
#if HAS_CLIENT == 1
	caps.AddCap(Capabilities::CAP_CLIENT);
#endif
#if HAS_SERVER==1
	caps.AddCap(Capabilities::CAP_SERVER);
#endif
#if HAS_UI==1
	caps.AddCap(Capabilities::CAP_UI)
#endif
	zeroConf->SetupPeer(caps, APP_ID);
	zeroConf->Start();
	discoveryThread = new std::thread([this]{discoveryLoop(); });
}
		
void Client::discoveryLoop()
{
	while (!shutdown)
	{
		std::vector<Peer> newPeers, newServers;
		std::vector<Peer> peers=zeroConf->DiscoverPeers();
		for (std::vector<Peer>::iterator it = peers.begin(); it != peers.end(); ++it)
		{
			try
			{	
				Capabilities peerCaps = it->GetCapabilities();
				std::string hostID = peerCaps.GetHostID();
				if (peerCaps.HasCap(Capabilities::CAP_SERVER) || peerCaps.HasCap(Capabilities::CAP_CLIENT))
				{
					bool found = false;
					std::vector<std::string> ds;
					for (int i = 0; i < discoveredServers.size(); ++i)
						ds.push_back(discoveredServers[i]);
					for (std::vector<std::string>::iterator nit = ds.begin();
						nit != ds.end();
						++nit)
					{
						if (std::strcmp((*nit).c_str(), it->GetCapabilities().GetHostID().c_str()) != 0)
						{
							found = true;
							nit = discoveredServers.end();
						}
					}
					if (found == false)
					{
						std::stringstream ss;
						ss << "Discovered peer: " << it->GetCapabilities().GetHostname();
						log->LogI(ss.str());
						newPeers.push_back(*it);
						if (it->GetCapabilities().HasCap(Capabilities::CAP_SERVER))
							newServers.push_back(*it);
					}
				}
				
				// So we have newly discovered clients or servers
				for (std::vector<Peer>::iterator it = newPeers.begin();
					it != newPeers.end();
					++it)
				{
					// First, if its a server, we need to set it up as such
					if (it->GetCapabilities().HasCap(Capabilities::CAP_SERVER))
					{
						// Add to discovered servers
						discoveredServers.push_back(it->GetCapabilities().GetHostname());
					}
				}
			}
			catch (const std::exception&)
			{
				
			}
		}
		
		// We need to do a few things with servers
		// Register them with the device manager as an event targer
		// Register them with the logger for a log target
		// Finially we need to send a host registration request
		for (std::vector<Peer>::iterator it = newServers.begin();
			it != newServers.end();
			++it)
		{
			dm->AddServerEndpoint(it->GetCapabilities().GetHostname());
			log->AddLogServerSink(it->GetCapabilities().GetHostname(), it->GetCapabilities().GetComPort());
			std::stringstream ss;
			ss << "Discovered new server: " << it->GetCapabilities().GetHostname();
			HostRegistration hr;
			for(std::vector<DeviceBase*>::iterator it=dm->GetAllDevices().begin();
				it!=dm->GetAllDevices().end();
				++it)
				{
					hr.AddDevice(*it);
				}
			if (RegClient::RegisterToServer(hr, it->GetCapabilities().GetHostname(), it->GetCapabilities().GetComPort()))
			{
				std::stringstream ss;
				ss << "Registered to server: " << it->GetCapabilities().GetHostname() << " successfully";
				log->LogI(ss.str());				
			}
			else
			{
				std::stringstream ss;
				ss << "FAILED to register to server: " << it->GetCapabilities().GetHostname();
				log->LogC(ss.str());
				
				// Remove this guy from teh seen list, and let it try again next cycle
				std::vector<std::string> ds;
				for (int i = 0; i < discoveredServers.size(); i++)
					if (std::strcmp(discoveredServers[i].c_str(), it->GetCapabilities().GetHostname().c_str()) != 0)
						ds.push_back(discoveredServers[i]);
				discoveredServers.clear();
				for (int i = 0; i < ds.size(); i++)
					discoveredServers.push_back(ds[i]);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	Client client();
	
}