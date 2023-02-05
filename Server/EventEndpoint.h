#pragma once

#include <string>
#include <algorithm>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <cjson/cJSON.h>

#include "Logger.h"
#include "../SensorEvent/SensorEvent.h"
#include "DB.h"

using namespace Pistache;

class EventEndpoint
{
public:
	EventEndpoint()
	{};
	static Pistache::Rest::Route::Result  ExecEventEndpoint(const Rest::Request& request, Http::ResponseWriter response);

};