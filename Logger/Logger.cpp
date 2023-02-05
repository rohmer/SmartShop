#include "Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{
	auto rolling = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs.txt", 1024 * 1024 * 10, 3);
	rolling->set_level(spdlog::level::trace);
	logPtr = std::make_shared<spdlog::logger>("SmartShop");
	logPtr->sinks().push_back(rolling);
}

void Logger::Init(bool isServer)
{
	if (isServer)
	{
		auto sink = std::make_shared<db_sink_mt>();	
		sink->set_level(spdlog::level::warn);
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