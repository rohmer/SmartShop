#pragma once

#include <string>
#include <thread>

#include "../Logger/Logger.h"
#include "../ZeroConf/ZeroConf.h"

class Discovery
{
public:
	Discovery();
	~Discovery();
	
	Capabilities GetFoundPeers()
	{
		return foundIDs;
	}
private:
	ZeroConf *zeroConfig;
	std::thread *discoveryThread;
	void discoveryLoop();
	bool shutdown;
	std::map<std::string, Capabilities> foundIDs;
};
