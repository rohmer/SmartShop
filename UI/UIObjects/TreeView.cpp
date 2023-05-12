#include "TreeView.h"

std::vector<TreeNode*> TreeView::rootNodes;

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

TreeView::~TreeView()
{
	for (int i = 0; i < rootNodes.size(); i++)
		if (rootNodes[i] != NULL)
			delete (rootNodes[i]);
	rootNodes.clear();
}

TreeNode* TreeView::AddRootNode(std::string Label, lv_obj_t *DisplayObject)
{
	TreeNode* node = TreeNode::CreateNode(lv_win_get_content(treeViewWindow), Label, DisplayObject);
	rootNodes.push_back(node);
	if (options.DefaultToExpanded())
	{
		node->visable = true;
		node->expanded = true;
	}
	redraw();
	return node;
}

TreeNode* TreeView::AddNode(std::string Label, lv_obj_t *DisplayObject, TreeNode* parent)
{
	if (parent == NULL)
		return AddRootNode(Label, DisplayObject);
	TreeNode* node = TreeNode::CreateNode(lv_win_get_content(treeViewWindow), Label, DisplayObject);
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
	
}

void TreeView::redraw(bool full)
{
	if (rootNodes.size() == 0 || full)
	{
		lv_obj_clean(lv_win_get_content(treeViewWindow));		
	}	
	uint y = 5;

	for (int i = 0; i < rootNodes.size(); i++)
	{
		y = drawNode(rootNodes[i], y, 1);
	}
}


uint TreeView::drawNode(TreeNode* node, uint y, uint depth)
{
	if (node->height == 0)
	{
		node->height = lv_font_default()->line_height + 2;
		if (node->displayObject != NULL)
		{
			if (lv_obj_get_height(node->displayObject) > height)
				node->height = lv_obj_get_height(node->displayObject);
			lv_obj_align_to(node->displayObject, node->labelObject, LV_ALIGN_OUT_RIGHT_MID, 3, 0);
		}
	}
	if (node->parentNode==NULL || (node->parentNode != NULL && node->parentNode->expanded))
		node->visable = true;
	else
		node->visable = false;
	if (node->visable)
	{
		lv_obj_set_pos(node->labelObject, depth * options.GetSetbackSize() + 5 + lv_font_default()->line_height, y);
		y += node->height;
		node->depth = depth;
		
		if (lineAnchor == NULL)
			drawAnchor(lv_win_get_content(treeViewWindow), node);
		else
			drawAnchor(lineAnchor, node);
		createTouchTarget(node);
		if (node->labelObject != NULL)
			lv_obj_clear_flag(node->labelObject, LV_OBJ_FLAG_HIDDEN);
		if (node->displayObject != NULL)
			lv_obj_clear_flag(node->displayObject, LV_OBJ_FLAG_HIDDEN);
		if (node->anchorObject != NULL)
		{
			lv_obj_clear_flag(node->anchorObject, LV_OBJ_FLAG_HIDDEN);
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

void TreeView::drawAnchor(lv_obj_t *parent, TreeNode *node)
{
	if (node->anchorObject == NULL)
		node->anchorObject = lv_img_create(parent);

	if (lineAnchor == NULL)
	{
		lineAnchor = node->anchorObject;
#ifdef DEBUG
		std::cout << node->label << ": Line Anchor\n";
#endif
	}
	if (node->GetChildren().size() > 0)
	{
		if (node->expanded)
			lv_img_set_src(node->anchorObject, LV_SYMBOL_RIGHT);
		else
			lv_img_set_src(node->anchorObject, LV_SYMBOL_DOWN);
	}
	else
	{
		lv_img_set_src(node->anchorObject, LV_SYMBOL_MINUS);
	}

	lv_obj_set_style_img_recolor(node->anchorObject, options.GetAnchorColor(), 0);
	lv_img_set_size_mode(node->anchorObject, LV_IMG_SIZE_MODE_REAL);
	lv_obj_align_to(node->anchorObject, node->labelObject, LV_ALIGN_OUT_LEFT_MID, -3, 0);

	
}

void TreeView::createTouchTarget(TreeNode *node)
{
	if (node->children.size() == 0 || node->labelObject == NULL || node->anchorObject == NULL)
		return;
	if (node->touchEventData == NULL)
	{
#ifdef DEBUG
		std::cout << node->label << " : touchEventData\n";
#endif
		node->touchEventData = new TreeNode::sTouchEventCB();
	}
	node->touchEventData->node = node;
	node->touchEventData->treeView = this;
	lv_obj_add_event_cb(node->anchorObject, touchEventCB, LV_EVENT_CLICKED, (void *)node->touchEventData);
	lv_obj_add_event_cb(node->labelObject, touchEventCB, LV_EVENT_CLICKED, (void *)node->touchEventData);
	lv_obj_add_flag(node->anchorObject, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(node->labelObject, LV_OBJ_FLAG_CLICKABLE);
}

void TreeView::touchEventCB(lv_event_t *evt)
{
	TreeNode::sTouchEventCB *data = (TreeNode::sTouchEventCB *)lv_event_get_user_data(evt);

#ifdef DEBUG
	std::cout << "Node: " << data->node->label << " touched\n";
#endif

	TreeView *tv = data->treeView;
	TreeNode *tn = data->node;
	tn->expanded = !tn->expanded;
	tv->redraw();
}
