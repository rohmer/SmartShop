#include "Init.h"

bool Init::isInit = false;
Config *Init::config = Config::GetInstance();
	
bool Init::InitServer()
{
	if (isInit)
		return true;
	// Initialize the db
	DB::GetInstance("SmartShop.db");
	
	// Initialize/Load the config
	if (!config->LoadConfig(DEFAULT_CONFIG_NAME))
	{
		// Failed to load the config, lets save out the default and move on
		config->SaveConfig(DEFAULT_CONFIG_NAME);
	}
	
	// Initalize the Logger
	DeviceConfig logConfig = config->GetLogConfig();
	
	uint restPort = logConfig.GetConfigItem("RESTPort").GetLongVal();
	
	Logger::GetInstance();
	Logger::GetInstance()->Update(
		logConfig.GetConfigItem("STDIO").GetBoolVal(),
		logConfig.GetConfigItem("DB").GetBoolVal(),
		logConfig.GetConfigItem("RESTLog").GetBoolVal(),
		(ELogLevel)logConfig.GetConfigItem("STDIOLevel").GetLongVal(),
		(ELogLevel)logConfig.GetConfigItem("DBLevel").GetLongVal(),
		(ELogLevel)logConfig.GetConfigItem("RESTLevel").GetLongVal(),
		restPort,
		config->GetRestLogServers());
	
	Logger::GetInstance()->LogI("1 - DB init");
	Logger::GetInstance()->LogI("2 - Config Init");
	Logger::GetInstance()->LogI("3 - Logger Init");
	
	DeviceConfig restConfig = config->GetServerConfig();
	RESTServer *restServer = RESTServer::GetInstance(
		restConfig.GetConfigItem("Port").GetLongVal(), 
		restConfig.GetConfigItem("Threads").GetLongVal());
	Logger::GetInstance()->LogI("4 - REST Server Created");
	
	DeviceConfig taConfig = config->GetTelemetryAgentConfig();
	if (taConfig.GetConfigItem("Enabled").GetBoolVal())
	{
		DeviceManager *dm = DeviceManager::GetInstance();
		dm->AddDevice(new TelemetryAgent(taConfig));		
		Logger::GetInstance()->LogI("5 - Telemetry Agent configured and started");
	}
	else
	{
		Logger::GetInstance()->LogI("5 - Telemetry Agent is skipped for this device");
	}
	
	Capabilities caps(config->GetCapsConfig());
	if (caps.HasCap(Capabilities::CAP_SERVER))
		Logger::GetInstance()->LogI("CAP_SERVER in use");
	if (caps.HasCap(Capabilities::CAP_UI))
		Logger::GetInstance()->LogI("CAP_UI in use");
	if (caps.HasCap(Capabilities::CAP_CLIENT))
		Logger::GetInstance()->LogI("CAP_CLIENT in use");
	
	ZeroConf *zeroConf = ZeroConf::GetInstance();
	zeroConf->SetupPeer(caps);
	zeroConf->Start();
	
	Logger::GetInstance()->LogI("6 - ZeroConfig service running");
	
	
	
}