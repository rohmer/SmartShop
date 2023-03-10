#include "Configuration.h"

Configuration *Configuration::instance = NULL;
Configuration::Configuration()
{
}

Configuration *Configuration::GetInstance()
{
	if (instance == NULL)
		instance = new Configuration();
	return instance;
}

bool Configuration::Init()
{ 
	zeroConf = ZeroConf::GetInstance();
	Capabilities caps;
#if HAS_CLIENT==1
	caps.AddCap(Capabilities::eCaps::CAP_CLIENT);
#endif
#if HAS_SERVER==1
	caps.AddCap(Capabilities::eCaps::CAP_SERVER);
#endif
#if HAS_UI==1
	caps.AddCap(Capabilities::eCaps::CAP_UI);
#endif
	zeroConf->SetupPeer(caps, APP_ID);
	zeroConf->Start();
	
	readConfig();
}

void Configuration::readConfig()
{
	if (std::filesystem::exists("config.json"))
	{
		
	}
}