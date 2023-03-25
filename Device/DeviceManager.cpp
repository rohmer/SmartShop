#include "DeviceManager.h"

DeviceManager *DeviceManager::instance = NULL;

DeviceManager::DeviceManager()
	: log(Logger::GetInstance())
{
	scheduler = new Bosma::Scheduler(16);
	loadConfig();
	updateThread = new std::thread([this]{updateLoop(); });
}

DeviceManager::~DeviceManager()
{
	shutdown = true;
	for (int i = 0; i < devices.size(); i++)
		if (devices[i] != NULL)
			delete(devices[i]);
}

DeviceManager *DeviceManager::GetInstance()
{
	if (instance == NULL)
		instance = new DeviceManager();
	return instance;
}

void DeviceManager::scheduleSensor(Sensor *s)
{
	std::vector<SensorEvent> events = s->PollSensor();
	
	for (int i=0; i<events.size(); i++)
	{
		events[i].SetGroupID(events[i].GetGroupID());
		events[i].StoreToDB();	
		// Send to server at this point
		if (endpointClient != NULL)
		{
			endpointClient->SendEvent(events[i]);
		}
	}
}
	
void DeviceManager::AddDevice(DeviceBase *device)
{
	if (!init && device->GetBus() != eDeviceBus::NA)
	{
		int i=gpioInitialise();
		if (i < 0)
			log->LogC("Failed to init GPIO");
	}
	devices.push_back(device);
	DeviceConfig dc = device->GetConfig();
	std::string devName = device->GetName();
	std::string devID = HashLib::ComputeHash(devName);
	
	if (deviceConfigs.find(dc.GetName()) != deviceConfigs.end())
	{
		dc = deviceConfigs[dc.GetName()];
		device->SetConfig(dc);
	}
	if (deviceByBus.find(dc.GetDeviceBus()) == deviceByBus.end())
		deviceByBus[dc.GetDeviceBus()] = std::vector<DeviceBase *>();
	if (deviceByType.find(dc.GetDeviceType()) == deviceByType.end())
		deviceByType[dc.GetDeviceType()] = std::vector<DeviceBase *>();
	
	
	if (deviceByName.find(dc.GetName()) != deviceByName.end())
	{
		std::stringstream ss;
		ss << "Dupilicate Device Name: " << dc.GetName();
		log->LogW(ss.str());
		std::stringstream s;
		s << device->GetName() << deviceByType.size();
		devID = HashLib::ComputeHash(s.str());
	}
	dc.SetDeviceID(devID);
	deviceByBus[dc.GetDeviceBus()].push_back(device);
	deviceByType[dc.GetDeviceType()].push_back(device);
	deviceByName[dc.GetName()] = device;
	
	if (dc.GetDeviceType() == eDeviceType::SENSOR)
	{	
		if (device != nullptr)
		{
			Sensor *s = dynamic_cast<Sensor *>(device);
			uint16_t pollingInterval = device->GetPollingInterval();
			scheduler->every(std::chrono::seconds(pollingInterval),
				[s, this]()
				{
					scheduleSensor(s);
				});
		}
	}
}

void DeviceManager::rescheduleSensors()
{
	scheduler->ClearTasks();
	if (deviceByType.find(eDeviceType::SENSOR) != deviceByType.end())
	{
		for (std::vector<DeviceBase*>::iterator it = deviceByType[eDeviceType::SENSOR].begin();
			it != deviceByType[eDeviceType::SENSOR].end();
			++it)
		{
			Sensor *s = (Sensor *)*it;
			uint16_t pollingInterval = ((DeviceBase*)s)->GetPollingInterval();
			scheduler->every(std::chrono::seconds(pollingInterval),
				[s, this]()
				{
					scheduleSensor(s);
				});
		}
	}
}

std::vector<DeviceBase*> DeviceManager::GetDeviceByBus(eDeviceBus bus)
{
	if (deviceByBus.find(bus) == deviceByBus.end())
		deviceByBus[bus] = std::vector<DeviceBase*>();
	return deviceByBus[bus];
}

DeviceBase* DeviceManager::GetDeviceByName(std::string name)
{
	if (deviceByName.find(name) == deviceByName.end())
		return nullptr;
	return deviceByName[name];
}

std::vector<DeviceBase*> DeviceManager::GetDeviceByType(eDeviceType dType)
{
	if (deviceByType.find(dType) == deviceByType.end())
		deviceByType[dType] = std::vector<DeviceBase*>();
	return deviceByType[dType];
}

std::vector<DeviceBase *> DeviceManager::GetAllDevices()
{
	std::vector<DeviceBase*> ret;
	for (std::map<std::string, DeviceBase*>::iterator it = deviceByName.begin();
		it != deviceByName.end();
		++it)
		return ret;
}
	
bool DeviceManager::storeConfig()
{
	try
	{
		cJSON *deviceConfigFile = cJSON_CreateObject();
		cJSON *array = cJSON_CreateObject();
		for (std::map<std::string, DeviceBase*>::iterator it = deviceByName.begin();
			it != deviceByName.end();
			++it)
		{
			cJSON_AddItemToArray(array, it->second->GetConfig().ToJSON());
		}
		cJSON_AddArrayToObject(deviceConfigFile, "devices");
		std::ofstream file("devices.json", std::_S_out);
		file << cJSON_Print(deviceConfigFile);
		file.close();
		cJSON_Delete(deviceConfigFile);
		return true;
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Error writing device file, " << e.what();
		log->LogC(ss.str());
	}
	return true;
}

bool DeviceManager::loadConfig()
{
	try
	{
		if (!std::filesystem::exists("devices.json"))
			return true;
		std::ifstream file("devices.json", std::_S_in);
		std::string line;
		std::stringstream ss;
		if (file.is_open())
		{
			while (file)
			{
				std::getline(file, line);
				ss << line << '\n';
			}
		}
		file.close();
		cJSON *json = cJSON_Parse(ss.str().c_str());
		if (json != NULL && 
			cJSON_HasObjectItem(json, "devices") && 
			cJSON_IsArray(cJSON_GetObjectItem(json,"devices")))
		{
			cJSON *devObj;
			cJSON_ArrayForEach(devObj, cJSON_GetObjectItem(json, "devices"))
			{
				DeviceConfig dc = DeviceConfig::FromJSON(devObj);
				if (dc.GetName().size() > 0)
				{
					deviceConfigs[dc.GetName()] = dc;
				}
			}
		}
		return false;
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Error reading device config, " << e.what();
		log->LogC(ss.str());
		return false;
	}
}

std::vector<std::string> DeviceManager::GetServerEndpoints()
{
	return serverEndpoints;
}

void DeviceManager::AddServerEndpoint(std::string Server, uint port)
{
	if (endpointClient == NULL)
		endpointClient = EndpointClient::GetInstance();
	bool found = false;
	for (std::vector<std::string>::iterator it = serverEndpoints.begin();
		it != serverEndpoints.end();
		++it)
	{
		if (std::strcmp((*it).c_str(), Server.c_str()) == 0)
		{
			found = true;
			it = serverEndpoints.end();
		}
		
		if (found)
		{
			std::stringstream ss;
			ss << "Server: " << Server << " was already defined";
			log->LogI(ss.str());
			return;
		}
	}
	serverEndpoints.push_back(Server);
	endpointClient->AddServer(Server, port);
	std::stringstream ss;
	ss << "Server: " << Server << " regiestered";
	log->LogI(ss.str());
}

void DeviceManager::updateLoop()
{
	while (!shutdown)
	{
		for (int i = 0; i < devices.size(); i++)
		{
			if (devices[i] != NULL)
			{
				if (devices[i]->GetConfig().Modified)
				{
					devices[i]->UpdateConfig(devices[i]->GetConfig());
				}
			}
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
		
}