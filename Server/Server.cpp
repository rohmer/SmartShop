#include "Server.h"

#include "CPUInfo.h"

Server::Server()
{
	std::string cpuID = CPUInfo::GetCPUID();
	int cpuCount = CPUInfo::GetCPUCount();
	
	DB::GetInstance("SmartShop.db");
	log = Logger::GetInstance();
	log->Init();
	
	restServer = new RESTServer(HTTP_PORT);
	try
	{
		logEndpoint = new LogEndpoint();
		registerEP = new RegistrationEndpoint();
		eventEP = new EventEndpoint();
		
		if (!restServer->RegisterResource("/event", (httpserver::http_resource *)eventEP))
			log->LogC("Could not register event resource");
		else
			log->LogI("Registered /event");
		if (!restServer->RegisterResource("/log", (httpserver::http_resource *)logEndpoint))
			log->LogC("Could not register log resource");
		else
			log->LogI("Registered /log");
		if (!restServer->RegisterResource("/register", (httpserver::http_resource *)registerEP))
			log->LogC("Could not register event resource");
		else
			log->LogI("Registered /register");
		
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Error setting up RESTServer, err: " << e.what();
		log->LogC(ss.str());
	}
	
	
	Capabilities caps;
	caps.AddCap(Capabilities::CAP_SERVER);
#ifdef USE_UI
	caps.AddCap(Capabilities::CAP_UI);
#endif
	
	ZeroConf *zeroConf=ZeroConf::GetInstance();
	zeroConf->SetupPeer(caps);
	zeroConf->Start();
	
	deviceManager = DeviceManager::GetInstance();
	restServer->Start();
#ifndef DISABLE_TELEMETRY_AGENT

	deviceManager->AddDevice(new TelemetryAgent("TelemetryAgent","TelemetryAgent",10));
#endif
	deviceManager->AddServerEndpoint("localhost", HTTP_PORT);
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