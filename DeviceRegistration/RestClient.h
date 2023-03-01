#pragma once

#include <string>
#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

class RestClient : public oatpp::web::client::ApiClient 
{
#include OATPP_CODEGEN_BEGIN(ApiClient)
	API_CLIENT_INIT(RestClient)
	API_CALL("POST", "post", doPost, BODY_STRING(String, body))
#include OATPP_CODEGEN_END(ApiClient)
};