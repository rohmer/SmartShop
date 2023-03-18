#pragma once

#include <string>
#include <spdlog/sinks/rotating_file_sink.h>
#ifndef _LOGGER
#include "DBSink.h"
#include "JSONSync.h"
#include "RemoteSync.h"
#define _LOGGER
#endif

#include "LogLevel.h"
#include "LogMsg.h"
#include "../RaspUtils/CPUInfo.h"
#include "RemoteSync.h"

#ifdef DEBUG
#define LOGLEVEL spdlog::level::info
#else
#define LOGLEVEL spdlog::level::warn
#endif

class Logger
{
public:
	static Logger *GetInstance();
	~Logger();
	void LogW(std::string msg);
	void LogI(std::string msg);
	void LogC(std::string msg);
	
	void Log(ELogLevel severity, std::string msg);
	
	void AddLogServerSink(std::string server, uint port=8080);
	void Init(std::map<std::string,uint>servers, bool hasServer = true, uint ServerPort = 8080, bool isServer = false, spdlog::level::level_enum logLevel = LOGLEVEL);
	void Init(bool hasServers=false, uint ServerPort=8080,bool isServer = false, spdlog::level::level_enum logLevel = LOGLEVEL);

	
private:
	Logger();
	static Logger *instance;
	std::shared_ptr<spdlog::logger> logPtr;
	std::string hostID;
	std::map<std::string,uint> servers;
};