#pragma once

#include <string>
#include <vector>

#include <lvgl.h>
#include "TreeNode.h"

#define TABSIZE 8;

class TreeView
{
  public:
	enum eTreeViewConnector
	{
		SOLIDLINE,
		DASHEDLINE,
		NONE
	};

	TreeView(
		std::string title,
		uint x,
		uint y,
		uint width,
		uint height, 
		eTreeViewConnector connectorType=eTreeViewConnector::SOLIDLINE);

	TreeView(
		std::shared_ptr<TreeNode> rootNode,
		std::string title,
		uint x,
		uint y,
		uint width,
		uint height,
		eTreeViewConnector connectorType = eTreeViewConnector::SOLIDLINE);
	
	static void Redraw(lv_event_t *e);
	bool AddRootNode(std::shared_ptr<TreeNode> node);
	bool AddNodeToNode(std::shared_ptr<TreeNode> nodeTarget, std::shared_ptr<TreeNode> newNode);
	bool DeleteNode(std::shared_ptr<TreeNode> node);
	std::vector<std::shared_ptr<TreeNode>> GetAllNodes(std::shared_ptr<TreeNode> node = NULL);

  private:
	lv_obj_t *treeViewWindow;
	lv_obj_t *deleteButton,*moveDownButton,*copyButton,*pasteButton,*moveUpButton;
	uint x1, y1, x2, y2;
	static std::shared_ptr<TreeNode> rootNode;
	eTreeViewConnector connectorType;

	static std::vector<lv_obj_t *> connectorLines;
	uint nCtr = 1;
	static void drawNode(std::shared_ptr<TreeNode> node, uint y);
};