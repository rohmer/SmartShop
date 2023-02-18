#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port) :
	ws(httpserver::create_webserver(port).max_connections(8))
{

	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
}

void RESTServer::Start()
{
	
}

void RESTServer::Shutdown()
{

}