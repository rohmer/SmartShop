#include "TreeView.h"

std::shared_ptr<TreeNode> TreeView::rootNode;
std::vector<lv_obj_t *> TreeView::connectorLines;

TreeView::TreeView(
	std::string title,
	uint x,
	uint y,
	uint width,
	uint height,
	eTreeViewConnector connectorType)
{
	treeViewWindow=lv_win_create(lv_scr_act(),40);
	lv_obj_set_x(treeViewWindow, x);
	lv_obj_set_y(treeViewWindow, y);
	lv_obj_set_width(treeViewWindow, width);
	lv_obj_set_height(treeViewWindow, height);
	lv_win_add_title(treeViewWindow, title.c_str());
	deleteButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_TRASH,40);
	moveDownButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_UP,40);
	copyButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_COPY,40);
	pasteButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_PASTE,40);
	moveUpButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_UP,40);

	lv_obj_add_event_cb(treeViewWindow, Redraw, LV_EVENT_READY, (void *)this);
	x1=lv_obj_get_x(lv_win_get_content(treeViewWindow));
	x2 = lv_obj_get_x2(lv_win_get_content(treeViewWindow));
	y1 = lv_obj_get_y(lv_win_get_content(treeViewWindow));
	y2 = lv_obj_get_y2(lv_win_get_content(treeViewWindow));
}

TreeView::TreeView(
	std::shared_ptr<TreeNode> rootNode,
	std::string title,
	uint x,
	uint y,
	uint width,
	uint height,
	eTreeViewConnector connectorType)
{
	this->rootNode = rootNode;
	this->rootNode.get()->parent = NULL;
	lv_win_create(treeViewWindow, 40);
	lv_obj_set_x(treeViewWindow, x);
	lv_obj_set_y(treeViewWindow, y);
	lv_obj_set_width(treeViewWindow, width);
	lv_obj_set_height(treeViewWindow, height);
	deleteButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_TRASH, 40);
	moveDownButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_UP, 40);
	copyButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_COPY, 40);
	pasteButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_PASTE, 40);
	moveUpButton = lv_win_add_btn(treeViewWindow, LV_SYMBOL_UP, 40);

	lv_obj_add_event_cb(treeViewWindow, Redraw, LV_EVENT_READY, (void *)this);
	x1 = lv_obj_get_x(lv_win_get_content(treeViewWindow));
	x2 = lv_obj_get_x2(lv_win_get_content(treeViewWindow));
	y1 = lv_obj_get_y(lv_win_get_content(treeViewWindow));
	y2 = lv_obj_get_y2(lv_win_get_content(treeViewWindow));
}

void TreeView::Redraw(lv_event_t *e=NULL)
{
	TreeView *tv = (TreeView *)lv_event_get_user_data(e);
	int x = 5, y = 5;
	
	// This may end up getting optimized to not redraw all of them
	for (int i = 0; i < connectorLines.size(); i++)
		if (connectorLines[i] != NULL)
			lv_obj_del_async(connectorLines[i]);
	connectorLines.clear();

	drawNode(rootNode, y);
}

void TreeView::drawNode(std::shared_ptr<TreeNode> node, uint y)
{
	int depth = 0;
	std::shared_ptr<TreeNode> nodeTmp = node;
	while (nodeTmp.get()->parent != NULL)
	{
		nodeTmp = nodeTmp.get()->parent;
		depth++;
	}
}

bool TreeView::AddRootNode(std::shared_ptr<TreeNode> node)
{
	if (rootNode != NULL)
		return false;
	node.get()->parent = NULL;
	rootNode = node;
	Redraw();
	return true;
}

std::vector<std::shared_ptr<TreeNode>> TreeView::GetAllNodes(std::shared_ptr<TreeNode> node)
{
	std::vector < std::shared_ptr<TreeNode>> ret;
	if (node == NULL)
	{
		ret.push_back(node);
		node = rootNode;
	}

	if (node.get()->children.size() > 0)
	{
		for (std::vector<std::shared_ptr<TreeNode>>::iterator it = node.get()->children.begin();
			 it != node.get()->children.end();
			 ++it)
		{
			std::vector<std::shared_ptr<TreeNode>> childNodes = GetAllNodes(*it);
			ret.insert(ret.begin(), childNodes.begin(), childNodes.end());
		}
	}
	return ret;
}

bool TreeView::AddNodeToNode(std::shared_ptr<TreeNode> nodeTarget, std::shared_ptr<TreeNode> newNode)
{
	std::vector<std::shared_ptr<TreeNode>> nodes = GetAllNodes();
	for (std::vector<std::shared_ptr<TreeNode>>::iterator it = nodes.begin();
		 it != nodes.end(); ++it)
	{
		if (it->get()->id == nodeTarget.get()->id)
		{
			nCtr++;
			newNode.get()->id = nCtr;
			nodeTarget->AddChild(newNode);
			Redraw();
			return true;
		}
	}
	return false;
}

bool TreeView::DeleteNode(std::shared_ptr<TreeNode> nodeTarget)
{
	std::vector<std::shared_ptr<TreeNode>> children = nodeTarget.get()->children;
	for (std::vector<std::shared_ptr<TreeNode>>::iterator it = children.begin(); it != children.end(); ++it)
	{
		nodeTarget.reset();
		;
		Redraw();
		return true;
	}
	Redraw();
	return false;
}