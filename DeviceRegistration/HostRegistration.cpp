#include "HostRegistration.h"

HostRegistration::HostRegistration():
	cpuID(CPUInfo::GetCPUID()),
	cpuCount(CPUInfo::GetCPUCount()),
	deviceType(CPUInfo::GetPIBoardType()),
	hostname(CPUInfo::GetHostname())
{
	
}

void HostRegistration::AddDevice(DeviceBase *device)
{
	sDevice devReg;
	devReg.deviceBus = device->GetBus();
	devReg.deviceConfig = device->GetConfig();
	devReg.deviceDescription = device->GetDescription();
	devReg.deviceName = device->GetName();
	devReg.deviceType = device->GetType();
	devices.push_back(devReg);
}

HostRegistration::HostRegistration(std::string hostname, std::string cpuID, EPIType deviceType, uint cpuCount)
	: cpuCount(cpuCount)
	, hostname(hostname)
	, cpuID(cpuID)
	, deviceType(deviceType)
{
}

cJSON *HostRegistration::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "hostname", cJSON_CreateString(hostname.c_str()));
	cJSON_AddItemToObject(json, "cpuid", cJSON_CreateString(cpuID.c_str()));
	cJSON_AddItemToObject(json, "cpus", cJSON_CreateNumber(cpuCount));
	cJSON_AddItemToObject(json, "hosttype", cJSON_CreateNumber(deviceType));
	cJSON *devArr = cJSON_CreateArray();
	for (int i = 0; i < devices.size(); i++)
	{
		cJSON *j = deviceToJSON(devices[i]);
		cJSON_AddItemToArray(devArr, j);
	}
	cJSON_AddItemToObject(json, "devices", devArr);
	return json;
}

HostRegistration HostRegistration::FromJSON(cJSON *json)
{
	std::string hostname, cpuid;
	uint cpuCount;
	EPIType deviceType;
	
	if (cJSON_HasObjectItem(json, "hostname"))
	{
		hostname = cJSON_GetObjectItem(json, "hostname")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "cpuid"))
	{
		cpuid = cJSON_GetObjectItem(json, "cpuid")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "cpus"))
	{
		cpuCount = cJSON_GetObjectItem(json, "cpus")->valueint;
	}
	if (cJSON_HasObjectItem(json, "hosttype"))
	{
		deviceType = (EPIType)cJSON_GetObjectItem(json, "hosttype")->valueint;
	}
	HostRegistration hr(hostname, cpuid, deviceType, cpuCount);
	if (cJSON_HasObjectItem(json, "devices"))
	{
		cJSON *arr = cJSON_GetObjectItem(json, "devices");
		if (cJSON_IsArray(arr))
		{
			cJSON *dc;
			cJSON_ArrayForEach(dc, arr)
			{
				sDevice dev = deviceFromJSON(dc);
				hr.addDevReg(dev);
			}
		}
	}
	return hr;
}

void HostRegistration::addDevReg(sDevice dev)
{
	devices.push_back(dev);
}

cJSON *HostRegistration::deviceToJSON(sDevice device)
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "bus", cJSON_CreateNumber(device.deviceBus));
	cJSON_AddItemToObject(json, "type", cJSON_CreateNumber(device.deviceType));
	cJSON_AddItemToObject(json, "name", cJSON_CreateString(device.deviceName.c_str()));
	cJSON_AddItemToObject(json, "desc", cJSON_CreateString(device.deviceDescription.c_str()));
	cJSON_AddItemToObject(json, "config", device.deviceConfig.ToJSON());
	return json;
}

HostRegistration::sDevice HostRegistration::deviceFromJSON(cJSON *json)
{
	sDevice device;
	if (cJSON_HasObjectItem(json, "bus"))
	{
		device.deviceBus = (eDeviceBus)cJSON_GetObjectItem(json, "bus")->valueint;
	}
	if (cJSON_HasObjectItem(json, "type"))
	{
		device.deviceType = (eDeviceType)cJSON_GetObjectItem(json, "type")->valueint;
	}
	if (cJSON_HasObjectItem(json, "name"))
	{
		device.deviceName = cJSON_GetObjectItem(json, "name")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "desc"))
	{
		device.deviceDescription = cJSON_GetObjectItem(json, "desc")->valuestring;
	}
	if (cJSON_HasObjectItem(json, "config"))
	{
		device.deviceConfig = DeviceConfig::FromJSON(cJSON_GetObjectItem(json, "config"));
	}
	return device;
}