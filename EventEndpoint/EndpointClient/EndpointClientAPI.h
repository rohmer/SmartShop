#pragma once

#include <string>

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "../../Logger/Logger.h"

class EndpointClientAPI : public oatpp::web::client::ApiClient
{
#include OATPP_CODEGEN_BEGIN(ApiClient)
	API_CLIENT_INIT(EndpointClientAPI);
	
	API_CALL("POST", "/event", doPost, BODY_STRING(String, body))
#include OATPP_CODEGEN_END(ApiClient)
};