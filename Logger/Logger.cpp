#include "Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{
	auto rolling = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs.txt", 1024 * 1024 * 10, 3);
	rolling->set_level(spdlog::level::trace);
	logPtr = std::make_shared<spdlog::logger>("SmartShop");
	logPtr->sinks().push_back(rolling);
}

Logger::~Logger()
{
	logPtr->flush();
	if (instance)
		delete(instance);
}

void Logger::AddLogServerSink(std::string server,uint port)
{
	if (servers.find(server) == servers.end())
		return;
	servers.emplace(server, port);
}

void Logger::Init(bool hasServers, uint ServerPort, bool isServer, spdlog::level::level_enum logLevel)
{
	Init(std::map<std::string,uint>(), hasServers, ServerPort, isServer, logLevel);
}
	
void Logger::Init(
	std::map<std::string,uint>servers,
	bool hasServer ,
	uint ServerPort,
	bool isServer,
	spdlog::level::level_enum logLevel)
{
	if (isServer)
	{
		auto sink = std::make_shared<db_sink_mt>();	
		sink->set_level(logLevel);
		logPtr->sinks().push_back(sink);	
	}
	if (hasServer)
	{
		auto sink = std::make_shared<log_sync_mt>();
		sink->set_level(logLevel);
		for (std::map<std::string, uint>::iterator it = servers.begin();
			it != servers.end();
			++it)
		{
			this->servers.emplace(it->first, it->second);
			sink->AddClient(it->first, it->second);
		}
		logPtr->sinks().push_back(sink);
	}
	for (int i = 0; i < logPtr->sinks().size(); i++)
		logPtr->sinks()[i].get()->set_level(logLevel);
}

Logger *Logger::GetInstance()
{
	if (instance == NULL)
		instance = new Logger();
	return instance;
}

void Logger::Log(ELogLevel Severity, std::string msg)
{
	spdlog::level::level_enum level = spdlog::level::info;
	if (Severity == ELogLevel::CRITICAL)
		level = spdlog::level::critical;
	if (Severity == ELogLevel::WARN)
		level = spdlog::level::warn;
	logPtr->log(level, msg);
	logPtr->flush();
}

void Logger::LogI(std::string msg)
{
	Log(ELogLevel::INFO, msg);
}

void Logger::LogW(std::string msg)
{
	Log(ELogLevel::WARN, msg);
}

void Logger::LogC(std::string msg)
{
	Log(ELogLevel::CRITICAL, msg);
}