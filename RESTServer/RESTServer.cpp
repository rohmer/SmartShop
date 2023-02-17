#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port)
{
	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));
	httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
	auto opts = Pistache::Http::Endpoint::options()
                        .threads(static_cast<int>(4));
	httpEndpoint->init(opts);
	
	Pistache::Rest::Routes::Get(router, "/hello", Pistache::Rest::Routes::bind(&RESTServer::hello));
	httpEndpoint->setHandler(router.handler());
	
	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
}

void RESTServer::hello(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) 
{
	response.send(Pistache::Http::Code::Ok, "world!");
}

void RESTServer::Start()
{
	httpEndpoint->serveThreaded();
}