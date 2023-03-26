#include "Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{
	auto rolling = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs.txt", 1024 * 1024 * 10, 3);
	rolling->set_level(spdlog::level::trace);
	logPtr = std::make_shared<spdlog::logger>("SmartShop");
	logPtr->sinks().push_back(rolling);
#ifdef DEBUG
	auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	logPtr->sinks().push_back(console);
#endif	
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

void Logger::Update(
	bool useSTDIO, 
	bool useDB, 
	bool useREST, 
	ELogLevel stdioLevel, 
	ELogLevel dbLevel, 
	ELogLevel restLevel,
	uint restServerPort,
	std::vector<std::string> restServers)
{
	logPtr->sinks().clear();
	if (useREST)
	{		
		auto sink = std::make_shared<log_sync_mt>();
		switch (restLevel)
		{
		case ELogLevel::INFO:
			sink->set_level(spdlog::level::trace);
			break;
		case ELogLevel::WARN:
			sink->set_level(spdlog::level::warn);
			break;
		case ELogLevel::CRITICAL:
			sink->set_level(spdlog::level::critical);
		}
		this->servers.clear();
		for (int i = 0; i < restServers.size(); i++)
		{
			this->servers.emplace(restServers[i], restServerPort);
			sink->AddClient(restServers[i], restServerPort);
		}
		logPtr->sinks().push_back(sink);		
	}
	if (useSTDIO)
	{
		auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		logPtr->sinks().push_back(console);
	}
	if (useDB)
	{
		auto sink = std::make_shared<db_sink_mt>();	
		switch (dbLevel)
		{
		case ELogLevel::INFO:
			sink->set_level(spdlog::level::trace);
			break;
		case ELogLevel::WARN:
			sink->set_level(spdlog::level::warn);
			break;
		case ELogLevel::CRITICAL:
			sink->set_level(spdlog::level::critical);
		}
		logPtr->sinks().push_back(sink);	
	}
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