#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"

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
	
	
private:
	httpserver::webserver ws;

};