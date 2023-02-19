#include "RegisterEndpoint.h"

std::shared_ptr<httpserver::http_response> RegisterEndpoint::render_POST(const httpserver::http_request &request)
{
	std::string body(request.get_content());
	
	
	cJSON *doc;
	try
	{
		doc=cJSON_Parse(body.c_str());
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Error parsing log message");
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error parsing register message", 406, "text/plain"));		
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
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error storing registration",500,"text/plain"));		
	}
	return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("OK", 200, "text/plain"));	
}