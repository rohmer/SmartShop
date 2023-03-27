#include "Init.h"

bool Init::isInit = false;

bool Init::InitServer()
{
	// Initialize the db
	DB::GetInstance("SmartShop.db");
	Config config;
	if (!config.LoadConfig())
	{
		Logger::GetInstance()->LogW("Failed to load config, recreating with defaults");
		config.SaveConfig();
	}
	
	// Setup the logger
	LogConfig logConfig;
	logConfig.Update(config.GetLogConfig());
	
	// Setup the RESTServer
	ServerConfig serverConfig;
	serverConfig.Update(config.GetServerConfig());
	
	
}