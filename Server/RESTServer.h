#pragma once

#include <string>
#include <algorithm>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "Logger.h"

class RESTServer
{
public: 
	RESTServer();
	
private:
	Logger *log;
		
};