#pragma once

#include <string>
#include <algorithm>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <cjson/cJSON.h>

#include "Logger.h"
#include "LogMsg.h"
#include "DB.h"

using namespace Pistache;

class LogEndpoint
{
public:
	LogEndpoint()
	{};
	static Pistache::Rest::Route::Result  ExecLogEndpoint(const Rest::Request &request, Http::ResponseWriter response);

};