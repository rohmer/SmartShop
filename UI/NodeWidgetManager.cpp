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
	Update();
	return nodesToBeCreated;
}

UIWidget *NodeWidgetManager::CreateNodeWidget(std::string nodeID)
{
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

void NodeWidgetManager::Update()
{
	for (std::map<std::string, std::shared_ptr<NodeWidget>>::iterator it = nodeObjects.begin();
		it != nodeObjects.end();
		++it)
	{
		it->second->Update();
	}
}
