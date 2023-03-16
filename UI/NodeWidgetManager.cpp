#include "NodeWidgetManager.h"

/**
 **Manages the creating and maintence of nodes display
 * /param windowPane - This is the tab view area the nodes will be drawn on
	Most of these params can take the defaults */
NodeWidgetManager::NodeWidgetManager(lv_obj_t *windowPane, uint width, uint height)
	: log(Logger::GetInstance())
	, drawSurface(windowPane)
	, width(width)
	, height(height)
{
	nodeWidth = width / NODE_COLUMNS - (10*NODE_COLUMNS);
	nodeHeight = height / NODE_ROWS - 50 - (10*NODE_ROWS);
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

UIWidget *NodeWidgetManager::CreateNodeWidget(std::string nodeID)
{
	int px, py;
	px = nodePosition  % 5;
	if (nodePosition > 5)
		py = nodePosition / 5;
	else
		py = 0;
	int x, y;
	if (px == 0)
		x = 5;
	else
		x = (px*(nodeWidth + 10));
	if (py == 0)
		y = 5;
	else
		y = (py*(nodeHeight + 10));
	
	// SO now we have our dimensions:
	// x,y starting point
	// nodWidth, nodeHeight the size
	
	NodeWidget *nw = new NodeWidget();
	nw->SetID(nodeID);
	nw->Draw(drawSurface, false, nodeWidth, nodeHeight, x, y);
	knownNodes.emplace(nodeID,false);
}