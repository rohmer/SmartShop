#pragma once

#include <string>
#include <algorithm>

#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"

#include <cjson/cJSON.h>

#include "Logger.h"
#include "../SensorEvent/SensorEvent.h"
#include "DB.h"


class EventEndpoint
{
public:
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);
};