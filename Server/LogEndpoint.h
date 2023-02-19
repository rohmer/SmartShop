#pragma once

#include <string>
#include <algorithm>

#include <cjson/cJSON.h>
#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"

#include "Logger.h"
#include "LogMsg.h"
#include "DB.h"


class LogEndpoint : public httpserver::http_resource
{
public:
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);

};