#pragma once

#include <string>
#include <spdlog/sinks/rotating_file_sink.h>
#ifndef _LOGGER
#include "DBSink.h"
#define _LOGGER
#endif

#include "LogLevel.h"
#include "LogMsg.h"

class Logger
{
public:
	static Logger *GetInstance();
	void LogW(std::string msg);
	void LogI(std::string msg);
	void LogC(std::string msg);
	
	void Log(ELogLevel severity, std::string msg);
	
	void Init(bool isServer = false);
private:
	Logger();
	static Logger *instance;
	std::shared_ptr<spdlog::logger> logPtr;
	
};