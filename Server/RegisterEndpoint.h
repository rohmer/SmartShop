#pragma once

#include <string>
#include <algorithm>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <cjson/cjson.h>

#include "../Device/DeviceConfig.h"
#include "Logger.h"
#include "LogMsg.h"
#include "DB.h"

using namespace Pistache;

class RegisterEndpoint
{
public:
	RegisterEndpoint()
	{}
	static Pistache::Rest::Route::Result  ExecRegisterEndpoint(const Rest::Request& request, Http::ResponseWriter response);


};