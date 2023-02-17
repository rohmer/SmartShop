#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "../Logger/Logger.h"

class RESTServer
{
public:
	enum eRestMethod
	{
		DELETE,
		GET,
		PATCH,
		POST,
		PUT
	};
	
	RESTServer(unsigned int port);
	void Start();
	void Shutdown();
	Pistache::Rest::Router GetRouter()
	{
		return router;
	}

private:
	std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
	Logger *log;
	Pistache::Rest::Router router;
};