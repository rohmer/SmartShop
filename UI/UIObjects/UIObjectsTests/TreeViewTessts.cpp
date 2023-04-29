#include <filesystem>
#include <string>
#include "../TreeView.h"
#include "../TreeNode.h"
#include "TestInitializer.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

TEST_GROUP(TreeNodes)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
		lv_obj_clean(lv_scr_act());
	}
};

TEST(TreeNodes, CreateNode)
{
	std::shared_ptr<TreeNode> tn1 = TreeNode::CreateTreeNode(lv_scr_act(), NULL, "Root Node", false, false, NULL);
}

TEST_GROUP(TreeView)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
	}
	
};

TEST(TreeView, CreateEmpty)
{
	TestInitializer::GetInstance()->InitializeInstance();
	std::shared_ptr<TreeView> treeView = std::make_shared<TreeView>(TreeView("Test TreeView Window", 10, 10, 300, 500));
	std::this_thread::sleep_for(std::chrono::seconds(100));
}