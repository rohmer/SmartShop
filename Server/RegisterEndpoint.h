#pragma once

#include <string>
#include <algorithm>

#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"
#include <cjson/cjson.h>

#include "../Device/DeviceConfig.h"
#include "Logger.h"
#include "LogMsg.h"
#include "DB.h"


class RegisterEndpoint : public httpserver::http_resource
{
public:	
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);


};