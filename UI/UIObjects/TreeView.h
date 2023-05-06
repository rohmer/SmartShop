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

	~TreeView();
	
	TreeNode* AddRootNode(std::string Label, lv_obj_t *DisplayObject=NULL);
	TreeNode* AddNode(std::string Label, lv_obj_t *DisplayObject, TreeNode* parent);

  private:
	TreeViewOptions options;
	uint x, y, width, height;
	lv_obj_t *treeViewWindow;
	static std::vector<TreeNode*> rootNodes;

	lv_obj_t *lineAnchor = NULL;
	void redraw(bool full=false);
	uint drawNode(TreeNode* node, uint y, uint depth);
	void setVisablity();
	void drawAnchor(lv_obj_t *parent, TreeNode* node);
	void createTouchTarget(TreeNode* node);
	static void touchEventCB(lv_event_t *e);
};