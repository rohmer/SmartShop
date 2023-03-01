#include "RegClient.h"

bool RegClient::RegisterToServer(HostRegistration hostReg, std::string server, uint port)
{
	try
	{
		std::string json = JSON::Print(hostReg.ToJSON());
		
		// Create the curl command and send it
		
	}
	catch (const std::exception&)
	{
		
	}
}