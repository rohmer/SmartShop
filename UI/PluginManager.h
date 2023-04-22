#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "dlclass.hpp"
#include "UIWidget/UIWidget.h"
#include "../Logger/Logger.h"

class PluginManager
{
public:
	static PluginManager *GetInstance();
	void LoadPlugins();
	
	std::shared_ptr<UIWidget> WidgetFactory(std::string name);

	std::map<std::string, DLClass<UIWidget> *> GetLoadedPlugins();

  private:
	static PluginManager *instance;
	PluginManager();
	
	std::map<std::string, DLClass<UIWidget>*> loadedPlugins;
	Logger *log;
};