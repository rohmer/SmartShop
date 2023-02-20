#pragma once

#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/base_sink.h>
#include <string>
#include <unistd.h>
#include "LogMsg.h"
#include "../DB/DB.h"
#include "../RaspUtils/CPUInfo.h"

template<typename Mutex>
	class DBSink : public spdlog::sinks::base_sink <Mutex>
	{
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
				DB::GetInstance()->GetStorage()->insert(logMsg);
			}
			catch (std::exception)
			{
			}
		}
		void flush_() override
		{
		}
	
	};

using db_sink_mt  = DBSink<std::mutex>;
using db_sink_st = DBSink<spdlog::details::null_mutex>;