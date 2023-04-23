#include "Client.h"


using namespace std;

Client::Client() :
	dm(DeviceManager::GetInstance())
{
	shutdown = false;
	restServer = RESTServer::GetInstance(SERVER_PORT, SERVER_THREADS);
	
	ConfigEndpoint *cfgEP = new ConfigEndpoint();
	restServer->RegisterResource("/config", (httpserver::http_resource *)cfgEP);
	
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
	discovery = new Discovery();
	
	
	
	dm->AddDevice("Telemetry Agent");
	
	// From here you add your additional devices, configure them as you need, etc.
	// They will get polled at their polling interval by the device manager, which also sends the  events to any discovered servers
}

void Client::Run()
{
	while (!shutdown)
	{
		
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
		
Client::~Client()
{
	delete(dm);
	restServer->Shutdown();	
}

int main(int argc, char *argv[])
{
	Client client();
	
}