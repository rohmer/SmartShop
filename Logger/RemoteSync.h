#pragma once

#include <map>
#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/base_sink.h>
#include <string>
#include <unistd.h>
#include "LogMsg.h"
#include "../DB/DB.h"
#include "../RaspUtils/CPUInfo.h"
#include "../RaspUtils/JSON.h"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/network/ConnectionPool.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "RemoteSyncAPI.h"

template<typename Mutex>
	class RemoteSync : public spdlog::sinks::base_sink <Mutex>
	{
	public:
		void AddClient(std::string clientAddr, uint port=8080)
		{
			bool exists = false;
			for (std::map<std::string, std::shared_ptr<RemoteSyncAPI>>::iterator it = clients.begin();
				it != clients.end();
				++it)
			{
				if (std::strcmp(it->first.c_str(), clientAddr.c_str()) == 0)
				{
					exists = true;
					it = clients.end();
				}
			}
			
			if (!exists)
			{
				using namespace oatpp::network;
				using namespace oatpp::web;
				using namespace oatpp::parser;
				const Address serverAddress(clientAddr, port, Address::IP_4);
				auto connectionProvider = tcp::client::ConnectionProvider::createShared(serverAddress);
				/* create connection pool */
				auto connectionPool = ClientConnectionPool::createShared(
				        connectionProvider /* connection provider */, 
					10 /* max connections */, 
					std::chrono::seconds(5) /* max lifetime of idle connection */
					);
				/* create retry policy */
				auto retryPolicy = std::make_shared<client::SimpleRetryPolicy>(2 /* max retries */, std::chrono::seconds(1) /* retry interval */);
				auto requestExecutor = client::HttpRequestExecutor::createShared(connectionPool, retryPolicy);
	
				auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
				std::shared_ptr<RemoteSyncAPI> client = RemoteSyncAPI::createShared(requestExecutor, objectMapper);
				clients.emplace(clientAddr, client);
			}
			
		}
	protected:
		void sink_it_(const spdlog::details::log_msg &msg) override
		{
			std::string hostID = CPUInfo::GetCPUID();
			char hostname[1024];
			gethostname(hostname, 1024);
			std::string host(hostname);
			LogMsg logMsg;
			logMsg.Host = host;
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
			logMsg.Message = fmt::to_string(formatted);
			logMsg.Timestamp = time(NULL);
			logMsg.HostID = hostID;
			ELogLevel level;
			switch (msg.level)
			{
			case spdlog::level::critical:
				level = ELogLevel::CRITICAL;
				break;
			case spdlog::level::debug:
				level = ELogLevel::INFO;
				break;
			case spdlog::level::trace:
				level = ELogLevel::INFO;
				break;
			case spdlog::level::err:
				level = ELogLevel::CRITICAL;
				break;
			case spdlog::level::warn:
				level = ELogLevel::WARN;
				break;
			case spdlog::level::info:
				level = ELogLevel::INFO;
				break;
			default:
				level = ELogLevel::WARN;
				break;
			}
			logMsg.Severity = level;
		
			try
			{
				std::string payload = JSON::Print(logMsg.ToJSON());
				for (std::map<std::string, std::shared_ptr<RemoteSyncAPI>>::iterator it = clients.begin();
					it != clients.end();
					++it)
				{
					std::string retBody=it->second->doPost(payload)->readBodyToString();
					if (std::strcmp(retBody.c_str(), "OK") != 0)
					{
						// Something went wrong, need to figure out what to do with it
					}
				}		
			}
			catch (const std::exception&)
			{
				// Again, do something if we fail to log
			}
		}
		
		void flush_() override
		{
		}
		
		std::map<std::string, std::shared_ptr<RemoteSyncAPI>> clients;
	};

using log_sync_mt = RemoteSync<std::mutex>;
using log_sync_st = RemoteSync<spdlog::details::null_mutex>;