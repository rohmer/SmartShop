#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port) 
	//ws(httpserver::create_webserver(port).max_connections(CPUInfo::GetCPUCount()*4))
{
	
	ws = new httpserver::webserver(httpserver::create_webserver(port).max_connections(CPUInfo::GetCPUCount()*4));
	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
	
}

bool RESTServer::RegisterResource(std::string path, httpserver::http_resource *resource)
{
	return ws->register_resource(path, resource);	
}

void RESTServer::Start()
{
	ws->start(false);
}

void RESTServer::Shutdown()
{
	ws->stop();
}