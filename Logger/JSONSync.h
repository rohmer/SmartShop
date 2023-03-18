#pragma once

#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/base_sink.h>
#include <string>
#include <unistd.h>

#include "cJSON.h"
#include "LogMsg.h"
#include "../Components/WebServer/httplib.h"

#include "../RaspUtils/CPUInfo.h"

template<typename Mutex>
	class JSONSync : public spdlog::sinks::base_sink <Mutex>
	{
	public:
		void SetServer(std::string serverName, uint port)
		{
			this->serverName = serverName;
			std::stringstream ss;
			ss << "http://" << serverName << ":" << port << "/log";
			serverURL = ss.str();
		}
		
	protected:
		std::string serverName, serverURL;
		uint port;
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
			
			cJSON *jMsg = cJSON_CreateObject();
			cJSON_AddItemToObject(jMsg, "host", cJSON_CreateString(logMsg.Host.c_str()));
			cJSON_AddItemToObject(jMsg, "msg", cJSON_CreateString(logMsg.Message.c_str()));
			cJSON_AddItemToObject(jMsg, "sev", cJSON_CreateNumber(logMsg.Severity));
			cJSON_AddItemToObject(jMsg, "hostid", cJSON_CreateString(logMsg.HostID.c_str()));
			cJSON_AddItemToObject(jMsg, "time", cJSON_CreateNumber(logMsg.Timestamp));
			
			std::string body = cJSON_Print(jMsg);
			cJSON_Delete(jMsg);
		
			httplib::Client cli(serverName,port);
			auto res = cli.Post(body);
			
			
			if (res->status != 200)
			{
				// Do something with the error
			}
		}
	};
	