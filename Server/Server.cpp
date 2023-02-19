#include "Server.h"

#include "CPUInfo.h"

Server::Server()
{
	std::string cpuID = CPUInfo::GetCPUID();
	int cpuCount = CPUInfo::GetCPUCount();
	
	DB::GetInstance("SmartShop.db");
	log = Logger::GetInstance();
	log->Init();
	
	restServer = new RESTServer(8080);
	LogEndpoint *logEndpoint = new LogEndpoint();
	RegisterEndpoint *registerEP = new RegisterEndpoint();
	EventEndpoint *eventEP = new EventEndpoint();
	restServer->RegisterResource("/log", (httpserver::http_resource *)logEndpoint);
	restServer->RegisterResource("/register", (httpserver::http_resource *)registerEP);
	restServer->RegisterResource("/event", (httpserver::http_resource *)eventEP);
	
	Capabilities caps;
	caps.AddCap(Capabilities::CAP_SERVER);
#ifdef USE_UI
	caps.AddCap(Capabilities::CAP_UI);
#endif
	
	ZeroConf zeroConf;
	zeroConf.SetupPeer(caps);
	zeroConf.Start();
	
	deviceManager = DeviceManager::GetInstance();
	restServer->Start();
}

int main(int argc, char *argv[])
{
	Server *server = new Server();
#ifdef USE_UI
	WindowManager *wm = WindowManager::GetInstance();
#endif 

		
	wm->Init();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}