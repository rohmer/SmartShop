#include "TreeView.h"

TreeView::TreeView(lv_obj_t *parent, uint X, uint Y, uint Width, uint Height, std::string Label, TreeViewOptions Options)
	: x(X),
	  y(Y),
	  width(Width),
	  height(Height),
	  options(Options)
{
	uint windowHeader = lv_font_default()->line_height + 2;
	if (!options.GetWindowHeader() && Label.size() == 0)
		windowHeader = 0;
	treeViewWindow = lv_win_create(parent, windowHeader);
	if (Label.size() > 0)
		lv_win_add_title(treeViewWindow, Label.c_str());
	lv_obj_set_pos(treeViewWindow, x, y);
	lv_obj_set_size(treeViewWindow, width, height);
	lv_obj_update_layout(treeViewWindow);
}

std::shared_ptr<TreeNode> TreeView::AddRootNode(std::string Label, lv_obj_t *DisplayObject)
{
	std::shared_ptr<TreeNode> node = TreeNode::CreateNode(lv_win_get_content(treeViewWindow), Label, DisplayObject);
	rootNodes.push_back(node);
	if (options.DefaultToExpanded())
	{
		node->visable = true;
		node->expanded = true;
	}
	redraw();
	return node;
}

std::shared_ptr<TreeNode> TreeView::AddNode(std::string Label, lv_obj_t *DisplayObject, std::shared_ptr<TreeNode> parent)
{
	if (parent == NULL)
		return AddRootNode(Label, DisplayObject);
	std::shared_ptr<TreeNode> node = TreeNode::CreateNode(lv_win_get_content(treeViewWindow), Label, DisplayObject);
	parent->AddChild(node);
	if (options.DefaultToExpanded())
	{
		node->visable = true;
		node->expanded = true;
	}
	redraw();
	return node;
}

void TreeView::setVisablity()
{
	for (int i = 0; i < rootNodes.size(); i++)
		rootNodes[i]->SetVisability(true);
}

void TreeView::redraw()
{
	if (rootNodes.size() == 0)
	{
		lv_obj_clean(lv_win_get_content(treeViewWindow));
		return;
	}
	setVisablity();
	uint y = 5;

	for (int i = 0; i < rootNodes.size(); i++)
	{
		y = drawNode(rootNodes[i], y, 1);
	}
}


uint TreeView::drawNode(std::shared_ptr<TreeNode> node, uint y, uint depth)
{
	if (node->height == 0)
	{
		node->height = lv_font_default()->line_height + 2;
		if (node->displayObject != NULL)
		{
			if (lv_obj_get_height(node->displayObject) > height)
				node->height = lv_obj_get_height(node->displayObject);
		}
	}
	if (node->visable)
	{
		lv_obj_set_pos(node->labelObject, depth * options.GetSetbackSize() + 5 + lv_font_default()->line_height, y);
		y += node->height;
		node->depth = depth;
		
		if (lineAnchor == NULL)
			lineAnchor = drawAnchor(lv_win_get_content(treeViewWindow), node);
		else
			drawAnchor(lineAnchor, node);
		if (node->labelObject != NULL)
			lv_obj_clear_flag(node->labelObject, LV_OBJ_FLAG_HIDDEN);
		if (node->displayObject != NULL)
			lv_obj_clear_flag(node->displayObject, LV_OBJ_FLAG_HIDDEN);
		if (node->anchorObject != NULL)
		{
			lv_obj_clear_flag(node->anchorObject, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(node->anchorObject, LV_OBJ_FLAG_CLICKABLE);
		}
		for (int i = 0; i < node->children.size(); i++)
			if (node->children[i]->visable)
			{
				y = drawNode(node->children[i], y, depth + 1);
			}
	}
	else
	{
		if (node->anchorObject != NULL)
		{
			lv_obj_add_flag(lineAnchor, LV_OBJ_FLAG_HIDDEN);
		}
		if (node->labelObject != NULL)
			lv_obj_add_flag(node->labelObject, LV_OBJ_FLAG_HIDDEN);
		if (node->displayObject != NULL)
			lv_obj_add_flag(node->displayObject, LV_OBJ_FLAG_HIDDEN);
	}

	return y;
}

lv_obj_t* TreeView::drawAnchor(lv_obj_t* parent, std::shared_ptr<TreeNode> node)
{
	if (node->children.size() == 0)
		return NULL;
	if(node->anchorObject==NULL)
		node->anchorObject = lv_img_create(parent);
	if (node->expanded)
		lv_img_set_src(node->anchorObject, LV_SYMBOL_PLUS);
	else
		lv_img_set_src(node->anchorObject,LV_SYMBOL_MINUS);

	lv_obj_set_style_img_recolor(node->anchorObject, options.GetAnchorColor(),0);
	lv_img_set_size_mode(node->anchorObject, LV_IMG_SIZE_MODE_REAL);
	lv_obj_align_to(node->anchorObject, node->labelObject, LV_ALIGN_OUT_LEFT_MID,0,0);
	return node->anchorObject;
}

