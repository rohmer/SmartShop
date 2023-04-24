#include "DevicePluginManager.h"

DevicePluginManager *DevicePluginManager::instance = NULL;

DevicePluginManager::DevicePluginManager()
	: log(Logger::GetInstance())
{
}

DevicePluginManager *DevicePluginManager::GetInstance()
{
	if (instance == NULL)
		instance = new DevicePluginManager();
	return instance;
}

void DevicePluginManager::LoadPlugins()
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path devicePath = cwd;
	devicePath /= "Devices";
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(devicePath))
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
					auto dlDevice = new DeviceLoader<DeviceBase>(p.string());
					std::shared_ptr<DeviceBase> widget = dlDevice->make_obj();
					if (widget != NULL)
					{
						loadedDevices.emplace(widget->GetName(), dlDevice);
					}
					widget.reset();
				}
				catch (std::exception &)
				{
				}
			}
		}
	}	
}

std::shared_ptr<DeviceBase> DevicePluginManager::DeviceFactory(std::string DeviceName)
{
	if (loadedDevices.find(DeviceName) == loadedDevices.end())
	{
		std::stringstream ss;
		ss << "Attempted to create unloaded plugin (" << DeviceName << ")";
		log->LogW(ss.str());
		return NULL;
	}
	
	return loadedDevices[DeviceName]->make_obj();	
}

std::map<std::string, DeviceLoader<DeviceBase> *> DevicePluginManager::GetLoadedDevices()
{
	return loadedDevices;
}