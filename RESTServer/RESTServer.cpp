#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port) :
	ws(httpserver::create_webserver(port).max_connections(8))
{

	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
	
}

void RESTServer::RegisterResource(std::string path, httpserver::http_resource *resource)
{
	ws.register_resource(path, resource);	
}

void RESTServer::Start()
{
	ws.start(false);
}

void RESTServer::Shutdown()
{
	ws.stop();
}