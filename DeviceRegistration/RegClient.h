#pragma once

#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "HostRegistration.h"
#include "../Logger/Logger.h"

#include "../Server/Settings.h"
#include "../RaspUtils/JSON.h"

class RegClient
{
public:
	static bool RegisterToServer(HostRegistration registration, std::string server, uint port=HTTP_PORT);
	
	
};