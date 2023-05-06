#include "TreeNode.h"

TreeNode::TreeNode(lv_obj_t *parent, std::string Label, lv_obj_t *DisplayObject) : parent(parent),
																				   label(Label),
																				   displayObject(DisplayObject)
{
	labelObject = lv_label_create(parent);
	lv_label_set_recolor(labelObject, true);
	lv_label_set_text(labelObject, Label.c_str());
	if (displayObject != NULL)
		lv_obj_align_to(displayObject, labelObject, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
}

std::shared_ptr<TreeNode> TreeNode::CreateNode(lv_obj_t *parent, std::string Label, lv_obj_t *DisplayObject)
{
	return std::make_shared<TreeNode>(TreeNode(parent, Label, DisplayObject));
}

std::vector<std::shared_ptr<TreeNode>> TreeNode::GetChildren()
{
	return children;
}

void TreeNode::AddChild(std::shared_ptr<TreeNode> child)
{
	child->parentNode = shared_from_this();
	children.push_back(child);
}

void TreeNode::SetVisability(bool v)
{
	visable = v;
	SetVisability();
}

void TreeNode::SetVisability()
{
	if (visable == false)
	{
		if (displayObject != NULL)
		{
			lv_obj_add_flag(displayObject, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(displayObject, LV_OBJ_FLAG_CLICKABLE);
		}
		if (labelObject != NULL)
		{
			lv_obj_add_flag(labelObject, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(labelObject, LV_OBJ_FLAG_CLICKABLE);
		}
		for (int i = 0; i < children.size(); i++)
			children[i]->SetVisability(false);
		return;
	}
	else
	{
		if (displayObject != NULL)
		{
			lv_obj_clear_flag(displayObject, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(displayObject, LV_OBJ_FLAG_CLICKABLE);
		}
		if (labelObject != NULL)
		{
			lv_obj_clear_flag(labelObject, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(labelObject, LV_OBJ_FLAG_CLICKABLE);
		}
		if(expanded)
			for (int i = 0; i < children.size(); i++)
				children[i]->SetVisability(true);
	}
}
