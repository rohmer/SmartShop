#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port)
{
	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));
	httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
	auto opts = Pistache::Http::Endpoint::options()
                        .threads(static_cast<int>(4));
	httpEndpoint->init(opts);
	
	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
}

void RESTServer::InitHandler()
{
	httpEndpoint->setHandler(router.handler());
}

void RESTServer::Start()
{
	httpEndpoint->serveThreaded();
}