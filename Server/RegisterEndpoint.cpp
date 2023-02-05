#include "RegisterEndpoint.h"

Pistache::Rest::Route::Result  RegisterEndpoint::ExecRegisterEndpoint(const Rest::Request &request, Http::ResponseWriter response)
{
	std::string body = request.body();
	
	cJSON *doc;
	try
	{
		doc=cJSON_Parse(body.c_str());
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Error parsing log message");
		response.send(Http::Code::Not_Acceptable);
		return Rest::Route::Result::Failure;
	}
	
	try
	{
		DeviceConfig dc = DeviceConfig::FromJSON(doc);
		if (dc.GetName().size() > 0 && dc.GetHostname().size()> 0)
		{
			if (!dc.ToDB())
				Logger::GetInstance()->LogW("Failed to store config in DB");
		}
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Failed to parse and store config");
		response.send(Http::Code::Not_Acceptable);
		return Rest::Route::Result::Failure;
	}
	response.send(Http::Code::Ok);
	return Rest::Route::Result::Ok;
}