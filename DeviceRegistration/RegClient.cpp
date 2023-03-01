#include "RegClient.h"
bool RegClient::RegisterToServer(HostRegistration hostReg, std::string server, uint port)
{
	try
	{
		std::string json = JSON::Print(hostReg.ToJSON());
		oatpp::base::Environment::init();
		auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({ server, port });
		
		auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
		auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
		auto client = RestClient::createShared(requestExecutor, objectMapper);
		std::string ret=client->doPost(json)->readBodyToString();
	}
	catch (std::exception &e)
	{
	}
}