#pragma once

#include <map>
#include <string>
#include <vector>
#include "NodeWidget/NodeWidget.h"
#include "../Logger/Logger.h"
#include "../DB/DB.h"

class NodeWidgetManager
{
public:
	NodeWidgetManager();
	std::vector<std::string> CheckNew();  // Returns a list of nodes that need to be drawn
	UIWidget *CreateNodeWidget(std::string nodeID, uint x, uint y, uint width, uint height);
	
private:
	std::map<std::string, bool> knownNodes;  // NodeID, If node is created
	Logger *log;
};