#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <lvgl.h>
#include "TreeNode.h"
#include "TreeViewOptions.h"
#include "lv_sline.h"

class TreeView
{
  public:
	TreeView(
		lv_obj_t *parent,
		uint X,
		uint Y,
		uint Width,
		uint Height,
		std::string Label,
		TreeViewOptions Options=TreeViewOptions());

	std::shared_ptr<TreeNode> AddRootNode(std::string Label, lv_obj_t *DisplayObject=NULL);
	std::shared_ptr<TreeNode> AddNode(std::string Label, lv_obj_t *DisplayObject, std::shared_ptr<TreeNode> parent);

  private:
	TreeViewOptions options;
	uint x, y, width, height;
	lv_obj_t *treeViewWindow;
	std::vector<std::shared_ptr<TreeNode>> rootNodes;

	lv_obj_t *lineAnchor = NULL;
	void redraw();
	uint drawNode(std::shared_ptr<TreeNode> node, uint y, uint depth);
	void setVisablity();
	lv_obj_t* drawAnchor(lv_obj_t *parent, std::shared_ptr<TreeNode> node);

};