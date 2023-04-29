#pragma once

#include <memory>
#include <string>
#include <vector>


#include <lvgl.h>
#include "TreeNode.h"

class TreeView;

struct TreeNode
{
  public:
	static std::shared_ptr<TreeNode> CreateTreeNode(lv_obj_t *treeViewCanvas,
											 std::shared_ptr<TreeNode> parent,
											 std::string labelText,
											 bool locked = false,
											 bool expanded = false,
											 lv_obj_t *payload = NULL);

	~TreeNode();

	void AddChild(std::shared_ptr<TreeNode> childNode);
	bool DeleteChild(std::shared_ptr<TreeNode> childNode);

	void SetVisibility(bool visible);
	void SetExpanded(bool expanded);

	void SetPosition(uint x, uint y);
	
	TreeNode(
		lv_obj_t *treeViewCanvas,
		std::shared_ptr<TreeNode> parent,
		std::string labelText,
		bool locked = false,
		bool expanded = false,
		lv_obj_t *payload = NULL);
	
  private:
	void createObjects();
	bool locked, expanded;
	std::shared_ptr<TreeNode> parent;
	std::vector<std::shared_ptr<TreeNode>> children;
	std::string labelTxt;
	lv_obj_t *payload, *label, *treeViewCanvas, *expandArrow = NULL;
	bool isVisible;

	friend class TreeView;
	uint id = 0;

	static void nodeClicked(lv_event_t *ev);
	void triggerRedraw();
};
