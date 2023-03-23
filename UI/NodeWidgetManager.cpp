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
	, pluginManager(PluginManager::GetInstance())
{
	nodeWidth = width / NODE_COLUMNS - (10*NODE_COLUMNS);
	nodeHeight = height / NODE_ROWS - 50 - (10*NODE_ROWS);
	lv_obj_set_flex_flow(windowPane, LV_FLEX_FLOW_ROW_WRAP);
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
	/*int px, py;
	px = nodePosition  % 3;
	if (nodePosition > 3)
		py = nodePosition / 3;
	else
		py = 0;
	int x, y;
	if (px == 0)
		x = 15;
	else
		x = (px*(nodeWidth + 25));
	if (py == 0)
		y = 5;
	else
		y = (py*(nodeHeight + 10));
	
	// SO now we have our dimensions:
	// x,y starting point
	// nodWidth, nodeHeight the size
	*/
	//std::shared_ptr<UIWidget> base = pluginManager->WidgetFactory("NodeWidget");
	std::shared_ptr<NodeWidget> nw = std::dynamic_pointer_cast<NodeWidget>(pluginManager->WidgetFactory("NodeWidget"));
	nw->SetID(nodeID);
	nw->Draw(drawSurface, false, nodeWidth, nodeHeight, -1, -1);
	std::stringstream ss;
	ss << "Creating node: " << nw->GetName() << " at (" << x << "," << y << ")";
	log->LogI(ss.str());
	nodeObjects.emplace(nodeID,nw);
	knownNodes.emplace(nodeID,false);
	nodePosition++;
}