#include "TreeNode.h"

TreeNode::TreeNode(
	lv_obj_t *treeViewCanvas,
	std::shared_ptr<TreeNode> parent,
	std::string labelText,
	bool locked,
	bool expanded,
	lv_obj_t *payload) : treeViewCanvas(treeViewCanvas),
						 parent(parent),
						 labelTxt(labelText),
						 locked(locked),
						 expanded(expanded),
						 payload(payload)
{
	if (parent!=NULL && parent.get()->expanded)
		isVisible = true;
	else
		isVisible = false;
	label = lv_label_create(treeViewCanvas);
	lv_label_set_text(label,labelTxt.c_str());
	if(payload!=NULL)
		lv_obj_align_to(payload, label, LV_ALIGN_OUT_RIGHT_MID, 2,0);
}

std::shared_ptr<TreeNode> TreeNode::CreateTreeNode(lv_obj_t *treeViewCanvas,
												   std::shared_ptr<TreeNode> parent,
												   std::string labelText,
												   bool locked,
												   bool expanded,
												   lv_obj_t *payload){
	return std::make_shared<TreeNode>(treeViewCanvas,
										 parent,
										 labelText,
										 locked,
										 expanded,
										 payload);
}
TreeNode::~TreeNode()
{
	if (payload != NULL)
		lv_obj_del_async(payload);
	if (label != NULL)
		lv_obj_del_async(label);
}

void TreeNode::createObjects()
{
	label = lv_label_create(treeViewCanvas);
	lv_label_set_text(label, labelTxt.c_str());
	if (payload != NULL)
		lv_obj_align_to(payload, label, LV_ALIGN_OUT_RIGHT_MID, 3, 0);

	lv_obj_add_event_cb(label, nodeClicked, LV_EVENT_CLICKED, (void *)this);
}

void TreeNode::SetVisibility(bool visibility)
{
	if (visibility)
	{
		lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(payload, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(payload, LV_OBJ_FLAG_HIDDEN);
	}
}

void TreeNode::AddChild(std::shared_ptr<TreeNode> child)
{
	if (children.size() == 0)
	{
		// We are adding a child, so we need to add the expand arrow
		expandArrow = lv_label_create(treeViewCanvas);
		lv_obj_align_to(expandArrow, label, LV_ALIGN_OUT_LEFT_MID, 3, 0);
		lv_obj_add_event_cb(expandArrow, nodeClicked, LV_EVENT_CLICKED, (void *)this);
	}
	if (expanded)
		lv_label_set_text(expandArrow, LV_SYMBOL_DOWN);
	else
		lv_label_set_text(expandArrow, LV_SYMBOL_RIGHT);
	lv_obj_add_event_cb(expandArrow, nodeClicked, LV_EVENT_CLICKED, (void *)this);
	children.push_back(child);
	triggerRedraw();
}

bool TreeNode::DeleteChild(std::shared_ptr<TreeNode> child)
{
	std::vector<std::shared_ptr<TreeNode>>::iterator p=children.end();
	for (std::vector<std::shared_ptr<TreeNode>>::iterator it = children.begin();
		 it != children.end();
		 ++it)
	{
		if (child.get()->id == it->get()->id)
			p = it;
	}
	if (p == children.end())
		return false;
	children.erase(p);
	while(p->get())
		p->reset();
	if (children.size() == 0)
	{
		lv_obj_del_async(expandArrow);
	}
	triggerRedraw();
	return true;
}

void TreeNode::SetExpanded(bool expanded)
{
	if (expanded)
	{
		if (expandArrow != NULL)
		{
			lv_label_set_text(expandArrow, LV_SYMBOL_DOWN);
		}	
		for (std::vector<std::shared_ptr<TreeNode>>::iterator it = children.begin();
			 it != children.end();
			 ++it)
		{
			it->get()->SetVisibility(true);
		}
	}
	else
	{
		if (expandArrow != NULL)
			lv_label_set_text(expandArrow, LV_SYMBOL_RIGHT);
	}
	triggerRedraw();
}

void TreeNode::triggerRedraw()
{
	lv_event_send(treeViewCanvas, LV_EVENT_READY, NULL);
}

void TreeNode::SetPosition(uint x, uint y)
{
	if (expandArrow != NULL)
		lv_obj_set_pos(expandArrow, x, y);
	else
		lv_obj_set_pos(label, x, y);
}

void TreeNode::nodeClicked(lv_event_t *ev)
{
}