#pragma once

#include <string>
#include <algorithm>

#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"

#include "cJSON.h"

#include "../Logger/Logger.h"
#include "../SensorEvent/SensorEvent.h"
#include "DB.h"
#include "../NodeAuth/NodeAuth.h"


class EventEndpoint : public httpserver::http_resource
{
public:
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);
	std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &request);
};