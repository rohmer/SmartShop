#pragma once

#include <string>

#include "../Components/WebServer/libhttpserver-master/src/httpserver.hpp"
#include "../Server/Settings.h"
#include "../DB/DB.h"

class NodeAuth
{
public:
	static bool IsNodeAuthorized(const httpserver::http_request &request);
};
