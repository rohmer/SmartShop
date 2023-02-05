#include "Server.h"

Server::Server()
{
	DB::GetInstance("SmartShop.db");
	log = Logger::GetInstance();
	log->Init();
	
	restServer = new RESTServer(8080);
	restServer->RegisterEndpoint("/log", RESTServer::POST, LogEndpoint::ExecLogEndpoint);
	restServer->RegisterEndpoint("/register", RESTServer::POST, RegisterEndpoint::ExecRegisterEndpoint);
	restServer->RegisterEndpoint("/event", RESTServer::POST, EventEndpoint::ExecEventEndpoint);

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