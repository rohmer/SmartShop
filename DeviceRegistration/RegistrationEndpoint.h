	#pragma once

#include <string>
#include <algorithm>

#include "cJSON.h"
#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"
#include "../Logger/Logger.h"
#include "DBDevice.h"
#include "../NodeAuth/NodeAuth.h"
#include "DB.h"
#include "HostRegistration.h"
#include "../Server/Settings.h"

class RegistrationEndpoint : public httpserver::http_resource
{
public:
	std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &request);
	std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &request);
};