#pragma once

#include <map>
#include <string>
#include <vector>
#include "NodeWidget/NodeWidget.h"
#include "../Logger/Logger.h"
#include "../DB/DB.h"
#include "Settings.h"
#include "PluginManager.h"

class NodeWidgetManager
{
public:
	NodeWidgetManager(lv_obj_t *windowPane, uint width, uint height);
	UIWidget *CreateNodeWidget(std::string nodeID);
	std::vector<std::string> CheckNew();
	void Update();
	
private:
	std::map<std::string, bool> knownNodes;  // NodeID, If node is created
	std::map<std::string, std::shared_ptr<NodeWidget>> nodeObjects; // NodeID, and Node UI Object
	Logger *log;
	uint displayedNodes;
	uint width, height, x, y;
	uint nodeWidth, nodeHeight;
	uint nodePosition=0;			//  This is the position of the next node to be created
	lv_obj_t *drawSurface;
	PluginManager *pluginManager;
};