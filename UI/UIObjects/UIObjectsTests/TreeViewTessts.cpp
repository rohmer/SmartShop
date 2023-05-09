#include <filesystem>
#include <string>
#include "../TreeView.h"
#include "../TreeNode.h"
#include "../TreeViewOptions.h"
#include "../../WindowManager.h"

#include "TestInitializer.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

#ifndef DISABLE_TREE_TESTS
TEST_GROUP(TreeNodes)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
	}
};

TEST_GROUP(TreeView)
{
	void setup()
	{
		TestInitializer::GetInstance()->InitializeInstance();
	}
	
};

TEST(TreeView, CreateEmpty)
{
	lv_obj_clean(lv_scr_act());
	std::shared_ptr<TreeView> treeView = std::make_shared<TreeView>(TreeView(lv_scr_act(), 0, 0, 500,500, "Test TreeView"));
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

TEST(TreeView, RootNodes)
{
	lv_obj_clean(lv_scr_act());
	std::shared_ptr<TreeView> treeView = std::make_shared<TreeView>(TreeView(lv_scr_act(), 0, 0, 500, 500, "Test TreeView"));
	treeView->AddRootNode("Root Node 1");
	treeView->AddRootNode("Root Node 2");
	treeView->AddRootNode("Root Node 3");
	treeView->AddRootNode("Root Node 4");
	treeView->AddRootNode("Root Node 5");
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

TEST(TreeView, WithChildren)
{
	lv_obj_clean(lv_scr_act());
	std::shared_ptr<TreeView> treeView = std::make_shared<TreeView>(TreeView(lv_scr_act(), 50, 50, 500, 500, "Test TreeView"));
	TreeNode *rn1 = treeView->AddRootNode("Root Node 1");
	treeView->AddNode("RN1 C1", NULL, rn1);
	TreeNode *rn11=treeView->AddNode("RN1 C2", NULL, rn1);
	treeView->AddNode("RN1 C1.1", NULL, rn11);
	treeView->AddNode("RN1 C2.2", NULL, rn11);
	treeView->AddNode("RN1 C3.3", NULL, rn11);
	
	treeView->AddNode("RN1 C3", NULL, rn1);
	TreeNode *rn2 = treeView->AddRootNode("Root Node 2");
	treeView->AddNode("RN2 C1", NULL, rn2);
	treeView->AddNode("RN2 C2", NULL, rn2);
	treeView->AddNode("RN2 C3", NULL, rn2);
	TreeNode *rn3 = treeView->AddRootNode("Root Node 3");
	treeView->AddNode("RN3 C1", NULL, rn3);
	treeView->AddNode("RN3 C2", NULL, rn3);
	treeView->AddNode("RN3 C3", NULL, rn3);
	std::this_thread::sleep_for(std::chrono::seconds(15));	
}

#endif