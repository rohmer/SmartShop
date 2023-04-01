#include "HostRegistration.h"
Config HostRegistration::config;

HostRegistration::HostRegistration():
	cpuID(CPUInfo::GetCPUID()),
	cpuCount(CPUInfo::GetCPUCount()),
	deviceType(CPUInfo::GetPIBoardType()),
	hostname(CPUInfo::GetHostname())
{
	ipAddress = CPUInfo::GetIPAddress();
}

HostRegistration::HostRegistration(
	std::string hostname, 
	std::string cpuID, 
	EPIType deviceType, 
	uint cpuCount, 
	std::string ipAddress,
	bool auth)
	: cpuCount(cpuCount)
	, hostname(hostname)
	, cpuID(cpuID)
	, deviceType(deviceType)
	, ipAddress(ipAddress)
	, isAuth(auth)
{
}

cJSON *HostRegistration::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "hostname", cJSON_CreateString(hostname.c_str()));
	cJSON_AddItemToObject(json, "cpuid", cJSON_CreateString(cpuID.c_str()));
	cJSON_AddItemToObject(json, "cpus", cJSON_CreateNumber(cpuCount));
	cJSON_AddItemToObject(json, "hosttype", cJSON_CreateNumber(deviceType));
	cJSON_AddItemToObject(json, "ip", cJSON_CreateString(ipAddress.c_str()));
	cJSON_AddItemToObject(json, "config", config.ToJSON());	
	return json;
}

HostRegistration HostRegistration::FromJSON(cJSON *json)
{
	std::string hostname, cpuid;
	uint cpuCount;
	EPIType deviceType;
	std::string ip;
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
	if (cJSON_HasObjectItem(json, "ip"))
	{
		ip = cJSON_GetObjectItem(json, "ip")->valuestring;		
	}
	if (cJSON_HasObjectItem(json, "config"))
	{
		config = Config::FromJSON(cJSON_GetObjectItem(json, "config"));	
	}
	HostRegistration hr(hostname, cpuid, deviceType, cpuCount, ip);
	
	return hr;
}

bool HostRegistration::StoreToDB()
{
	using namespace sqlite_orm;
	long id;
	try
	{
		auto dev = DB::GetInstance()->GetStorage()->get_pointer<DBDevice>(where(c(&DBDevice::CPUID) == cpuID));
		if (dev == NULL)
		{
			id = -1;
		}
		else
		{
			id = dev->ID;
		}
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Exception storing host registration to db: " << e.what();
		Logger::GetInstance()->LogC(ss.str());
		return false;
	}
	DBDevice dev;
	dev.CPUCount = cpuCount;
	dev.CPUID = cpuID;
	dev.DeviceType = deviceType;
	dev.Hostname = hostname;
	if (id != -1)
		dev.ID = id;
	dev.IPAddress = ipAddress;
	dev.isAuth = isAuth;
	if (id != -1)
	{
		DB::GetInstance()->GetStorage()->update(dev);
	}
	else
	{
		id = DB::GetInstance()->GetStorage()->insert<DBDevice>(dev);
	}
	
	std::vector<DeviceConfig> devices = GetDevices();
	for (std::vector<DeviceConfig>::iterator it = devices.begin();
		it != devices.end();
		++it)
	{
		it->ToDB();
	}
	
	return true;
}

HostRegistration HostRegistration::FromDB(std::string cpuID)
{
	using namespace sqlite_orm;
	auto hostReg = DB::GetInstance()->GetStorage()->get_pointer<DBDevice>(where(c(&DBDevice::CPUID) == cpuID));
	if (hostReg == NULL)
	{
		return HostRegistration();
	}
	HostRegistration reg(hostReg->Hostname, hostReg->CPUID, (EPIType)hostReg->DeviceType, hostReg->CPUCount, hostReg->IPAddress, hostReg->isAuth);
	
	std::vector<DeviceConfig> dc = DeviceConfig::FromDB(hostReg->CPUID);
	for(int i=0; i<dc.size(); i++)
		reg.AddDevice(dc[i]);
	
		
}