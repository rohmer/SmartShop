#include "RESTServer.h"
RESTServer *RESTServer::instance;

RESTServer *RESTServer::GetInstance(uint ServerPort, uint ServerThreads)
{
	if (instance == NULL)
		instance = new RESTServer(ServerPort, ServerThreads);
	return instance;
}

RESTServer::RESTServer(unsigned int port, uint threads) 
	//ws(httpserver::create_webserver(port).max_connections(CPUInfo::GetCPUCount()*4))
{
	ws = new httpserver::webserver(httpserver::create_webserver(port).max_connections(threads));
	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
}

void RESTServer::Update(uint ServerPort, uint ServerThreads)
{
	Logger::GetInstance()->LogI("Reconfiguring REST Server");
	if (ws!=NULL && ws->is_running())
		ws->stop();
	delete(ws);
	ws=new httpserver::webserver(httpserver::create_webserver(ServerPort).max_connections(ServerThreads));
	for (std::map<std::string, httpserver::http_resource*>::iterator it = resources.begin();
		it != resources.end();
		++it)
	{
		if (ws->register_resource(it->first, it->second))
		{
			std::stringstream ss;
			ss << "Registered: " << it->first << " resource";
			Logger::GetInstance()->LogI(ss.str());
		}
		else
		{
			std::stringstream ss;
			ss << "Failed to register: " << it->first << " resource";
			Logger::GetInstance()->LogC(ss.str());
		}
	}
	if (ws->is_running())
	{
		Logger::GetInstance()->LogI("REST Server reconfigured");
	}
	else
	{
		Logger::GetInstance()->LogC("REST Server failed to restart");
	}
}

bool RESTServer::RegisterResource(std::string path, httpserver::http_resource *resource)
{
	resources.emplace(path, resource);
	if (ws->register_resource(path, resource))
	{
		resources.emplace(path, resource);
		std::stringstream ss;
		ss << "Registered: " << path << " resource";
		Logger::GetInstance()->LogI(ss.str());
		return true;
	}
	std::stringstream ss;
	ss << "Failed to register: " << path << " resource";
	Logger::GetInstance()->LogC(ss.str());
	return false;
	
}

void RESTServer::Start()
{
	ws->start(false);
}

void RESTServer::Shutdown()
{
	ws->stop();
}