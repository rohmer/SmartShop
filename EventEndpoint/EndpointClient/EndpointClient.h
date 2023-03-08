#pragma once

#include <stack>
#include <string>
#include <thread>

#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/ConnectionPool.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "../../Logger/Logger.h"
#include "../../SensorEvent/SensorEvent.h"
#include "../../RaspUtils/JSON.h"

#include "EndpointClientAPI.h"

class EndpointClient
{
public:
	static EndpointClient *GetInstance();
	~EndpointClient();
	void Init(std::string server, uint port);
	
private:
	static EndpointClient *instance;
	EndpointClient();
	void eventLoop();
	void sendEvents();
	
	Logger *log;
	
	std::string server;
	uint port;
	
	bool shutdown = false;
	std::thread *threadObj;
	std::stack<SensorEvent> events;
	
	std::shared_ptr<EndpointClientAPI> client;
};