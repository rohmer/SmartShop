#include "PluginManager.h"

PluginManager *PluginManager::instance = NULL;

PluginManager::PluginManager() :
	log(Logger::GetInstance())
{
}

PluginManager *PluginManager::GetInstance()
{
	if (instance == NULL)
		instance = new PluginManager();
	return instance;
}

void PluginManager::LoadPlugins()
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path uiPath = cwd;
	uiPath /= "UI";
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(uiPath))
	{
		if (entry.is_regular_file())
		{
			std::filesystem::path p = entry.path();
			if (p.extension().string() == ".so" && p.filename().string() != "UIWidget.so")
			{
				std::stringstream ss;
				ss << "Attempting to load: " << p.string();
				log->LogI(ss.str());
				
				try
				{
					auto dlWidget = new DLClass<UIWidget>(p.string());
					std::shared_ptr<UIWidget> widget = dlWidget->make_obj();
					if (widget != NULL)
					{
						loadedPlugins.emplace(widget->GetName(), dlWidget);
					}
				}
				catch (std::exception &)
				{
				}
			}
		}
	}
}

std::shared_ptr<UIWidget> PluginManager::WidgetFactory(std::string WidgetName)
{
	if (loadedPlugins.find(WidgetName) == loadedPlugins.end())
	{
		std::stringstream ss;
		ss << "Attempted to create unloaded plugin (" << WidgetName << ")";
		log->LogW(ss.str());
		return NULL;
	}
	
	return loadedPlugins[WidgetName]->make_obj();	
}

std::map<std::string, DLClass<UIWidget> *> PluginManager::GetLoadedPlugins()
{
	return loadedPlugins;
}