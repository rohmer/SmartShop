#pragma once

#include <string>

#include "HostRegistration.h"
#include "../Logger/Logger.h"

#include "../Server/Settings.h"
#include "../RaspUtils/JSON.h"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "RestClient.h"

class RegClient
{
public:
	static bool RegisterToServer(HostRegistration registration, std::string server, uint port=HTTP_PORT);
	
};