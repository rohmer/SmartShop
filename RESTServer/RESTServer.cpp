#include "RESTServer.h"

RESTServer::RESTServer(unsigned int port)
{
	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));
	httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
	auto opts = Pistache::Http::Endpoint::options()
                        .threads(static_cast<int>(4));
	httpEndpoint->init(opts);
	httpEndpoint->setHandler(router.handler());
	
	log = Logger::GetInstance();
	log->LogI("RESTServer Created");
}

void RESTServer::RegisterEndpoint(std::string path, 
	eRestMethod method, 
	std::function<Pistache::Rest::Route::Result(Pistache::Rest::Request,Pistache::Http::ResponseWriter)> restMethod)
{
	switch (method)
	{
	case DELETE:
		Pistache::Rest::Routes::Delete(router, path, restMethod);
		break;
	case GET:
		Pistache::Rest::Routes::Get(router, path, restMethod);
		break;
	case PATCH:
		Pistache::Rest::Routes::Patch(router, path, restMethod);
		break;
	case POST:
		Pistache::Rest::Routes::Post(router, path, restMethod);
		break;
	case PUT:
		Pistache::Rest::Routes::Put(router, path, restMethod);
		break;
	}
	
	std::stringstream ss;
	ss << "Registered route: " << path << " as type: " << method;
	log->LogI(ss.str());
}

void RESTServer::Start()
{
	httpEndpoint->serveThreaded();
}