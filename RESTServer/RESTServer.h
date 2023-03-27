#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"

#include "../Logger/Logger.h"
#include "../RaspUtils/CPUInfo.h"

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
	
	static RESTServer *GetInstance(uint ServerPort = 8080, uint ServerThreads = 16);
	
	void Start();
	void Shutdown();
	
	bool RegisterResource(std::string path, httpserver::http_resource *resource);
	
	void Update(uint ServerPort, uint ServerThreads);
	
private:
	RESTServer(unsigned int port, uint threads);
	static RESTServer *instance;
	
	httpserver::webserver *ws;
	Logger *log;
	std::map<std::string, httpserver::http_resource*> resources;
};