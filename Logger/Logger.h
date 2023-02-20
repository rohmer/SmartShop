#pragma once

#include <string>
#include <spdlog/sinks/rotating_file_sink.h>
#ifndef _LOGGER
#include "DBSink.h"
#include "JSONSync.h"
#define _LOGGER
#endif

#include "LogLevel.h"
#include "LogMsg.h"
#include "../RaspUtils/CPUInfo.h"

class Logger
{
public:
	static Logger *GetInstance();
	void LogW(std::string msg);
	void LogI(std::string msg);
	void LogC(std::string msg);
	
	void Log(ELogLevel severity, std::string msg);
	
	void Init(bool isServer = false, spdlog::level::level_enum logLevel = spdlog::level::warn);
	void RemoteLog(std::string Server, uint Port);
	
private:
	Logger();
	static Logger *instance;
	std::shared_ptr<spdlog::logger> logPtr;
	std::string hostID;
	
};