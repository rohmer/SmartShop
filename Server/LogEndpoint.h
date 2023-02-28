#pragma once

#include <string>
#include <algorithm>

#include <date.h>
#include <cjson/cJSON.h>
#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"
#include "Logger.h"
#include "LogMsg.h"
#include "../NodeAuth/NodeAuth.h"
#include "DB.h"


class LogEndpoint : public httpserver::http_resource
{
public:
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);
	std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &request);
	
};