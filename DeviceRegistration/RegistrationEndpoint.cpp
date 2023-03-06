#include "RegistrationEndpoint.h"

std::shared_ptr<httpserver::http_response> RegistrationEndpoint::render_POST(const httpserver::http_request &request)
{
	std::string body(request.get_content());
	HostRegistration hr;
	cJSON *doc;
	try
	{
		doc = cJSON_Parse(body.c_str());
		hr = HostRegistration::FromJSON(doc);
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Error parsing event message");
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error parsing registration message", 406, "text/plain"));				
	}
	
	try
	{		
		using namespace sqlite_orm;
		std::vector<DBDevice> dbd = DB::GetInstance()->GetStorage()->get_all<DBDevice>(where(c(&DBDevice::CPUID) == hr.GetCPUID()));
		
		DBDevice deviceEntry;
		deviceEntry.CPUCount = hr.GetCPUCount();
		deviceEntry.CPUID = hr.GetCPUID();
		deviceEntry.DeviceType = hr.GetDeviceType();
		deviceEntry.Hostname = hr.GetHostname();
		deviceEntry.isAuth = DEFAULT_AUTH;
		if (dbd.size() == 1)
		{			
			deviceEntry.ID = dbd[0].ID;
			DB::GetInstance()->GetStorage()->replace<DBDevice>(deviceEntry);
		}
		else
		{
			DB::GetInstance()->GetStorage()->insert(deviceEntry);
		}
		for (int i = 0; i < hr.GetDevices().size(); i++)
		{
			HostRegistration::sDevice dev = hr.GetDevices()[i];
			dev.deviceConfig.ToDB();
			
		}
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Exception storing registration, " << e.what();
		Logger::GetInstance()->LogC(ss.str());
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error storing registration", 406, "text/plain"));				
	}
	return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("OK", 200));
}