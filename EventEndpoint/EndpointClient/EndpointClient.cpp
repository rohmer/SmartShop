#include "EndpointClient.h"

EndpointClient *EndpointClient::instance = NULL;

EndpointClient::EndpointClient()
	: log(Logger::GetInstance())
{
	log->LogI("EndpointClient created");
}

EndpointClient *EndpointClient::GetInstance()
{
	if (instance == NULL)
	{
		instance = new EndpointClient();
	}
	return instance;
}

void EndpointClient::SendEvent(SensorEvent event)
{
	events.push(event);
}

void EndpointClient::AddServer(std::string server, uint port)
{
	shutdown = false;
	threadObj = new std::thread([this]{eventLoop(); });
	log->LogI("EndpointClient::eventLoop() started");
	this->server = server;
	using namespace oatpp::network;
	using namespace oatpp::web;
	using namespace oatpp::parser;
	const Address serverAddress(server, port, Address::IP_4);
	auto connectionProvider = tcp::client::ConnectionProvider::createShared(serverAddress);
	/* create connection pool */
	auto connectionPool = ClientConnectionPool::createShared(
	        connectionProvider /* connection provider */, 
	        10 /* max connections */, 
	        std::chrono::seconds(5) /* max lifetime of idle connection */
	        );
	/* create retry policy */
	auto retryPolicy = std::make_shared<client::SimpleRetryPolicy>(2 /* max retries */, std::chrono::seconds(1) /* retry interval */);
	auto requestExecutor = client::HttpRequestExecutor::createShared(connectionPool,retryPolicy);
	
	auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
	std::shared_ptr<EndpointClientAPI>client = EndpointClientAPI::createShared(requestExecutor,objectMapper);
	clients.push_back(client);
}

void EndpointClient::eventLoop()
{
	while (!shutdown)
	{
		if (events.size() > 0)
		{
			sendEvents();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void EndpointClient::sendEvents()
{
	while (events.size() > 0)
	{
		for (int i = 0; i < clients.size(); i++)
		{
			SensorEvent se = events.top();
			events.pop();
			std::shared_ptr<EndpointClientAPI> client = clients[i];
			try
			{
				std::string body = JSON::Print(se.ToJSON());
				std::string ret = client->doPost(body)->readBodyToString();	
			}
			catch (std::exception &e)
			{
				std::stringstream ss;
				ss << "Exception sending event to server, exception: " << e.what();
				log->LogC(ss.str());
			}
		}
	}
}
