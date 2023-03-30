#include "Server.h"

#include "CPUInfo.h"

Server::Server()
{
	if (!Init::InitServer())
	{
		// Do something and exit?
	}
	Config *config = Config::GetInstance();

	log = Logger::GetInstance();
	
	restServer = RESTServer::GetInstance();
	
	bool server = false;
#ifdef USE_SERVER
	server = true;
#endif
	if (server || config->GetCapsConfig().GetConfigItem("SERVER").GetBoolVal())
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