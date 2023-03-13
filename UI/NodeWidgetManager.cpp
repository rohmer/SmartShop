#include "NodeWidgetManager.h"

NodeWidgetManager::NodeWidgetManager() :
	log(Logger::GetInstance())
{
}

std::vector<std::string> NodeWidgetManager::CheckNew()
{
	std::vector<std::string> nodesToBeCreated;
	using namespace sqlite_orm;
	std::vector<DBDevice> dbd = DB::GetInstance()->GetStorage()->get_all<DBDevice>();
	for (std::vector<DBDevice>::iterator it = dbd.begin(); it != dbd.end(); ++it)
	{
		if (knownNodes.find(it->CPUID) == knownNodes.end())
		{
			knownNodes.emplace(it->CPUID, false);
			nodesToBeCreated.push_back(it->CPUID);
		}
	}
	return nodesToBeCreated;
}

UIWidget *NodeWidgetManager::CreateNodeWidget(std::string nodeID, uint x, uint y, uint width, uint height)
{
	
}