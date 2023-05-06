#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


#include <lvgl.h>
#include "TreeNode.h"
#include "TreeViewOptions.h"

class TreeView;

struct TreeNode 
	: public std::enable_shared_from_this <TreeNode>
{
  public:
	TreeNode(lv_obj_t *parent, std::string Label, lv_obj_t *displayObject);
	~TreeNode();
	static TreeNode* CreateNode(lv_obj_t *parent, std::string Label, lv_obj_t *displayObject);
	std::vector<TreeNode*> GetChildren();
	void AddChild(TreeNode* child);

	void SetVisability();
	void SetVisability(bool visable);

	void SetLabel(std::string expandChar, TreeViewOptions options);
		
  private:
	friend class TreeView;
	struct sTouchEventCB
	{
		TreeView *treeView;
		TreeNode *node;
	};
	sTouchEventCB *touchEventData = NULL;

	TreeNode* parentNode;
	std::string label;
	lv_obj_t *parent;
	lv_obj_t *displayObject = NULL;
	lv_obj_t *labelObject = NULL;
	lv_obj_t *anchorObject = NULL;
	std::vector<TreeNode*> children;	
	uint height = 0;
	bool expanded = false;
	bool visable = false;
	uint depth;
	lv_point_t connectorPoint;
};
