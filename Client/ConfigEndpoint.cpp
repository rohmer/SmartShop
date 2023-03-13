#include "ConfigEndpoint.h"

std::shared_ptr<httpserver::http_response> ConfigEndpoint::render_POST(const httpserver::http_request &request)
{
	std::string body(request.get_content());
	
	cJSON *doc;
	try
	{
		doc = cJSON_Parse(body.c_str());
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Error parsing event message");
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error parsing event message", 406, "text/plain"));				
	}

	// We should have gotten back and array of device configs named configs
	if (cJSON_HasObjectItem(doc, "configs"))
	{
		cJSON *array = cJSON_GetObjectItem(doc, "configs");
		if (!cJSON_IsArray(array))
		{
			Logger::GetInstance()->LogW("config item is not an array");
			return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("config item is not an array", 406, "text/plain"));				
		}
		
		// TODO: parse the configs and send them to the device manager to reconfig
		
	}
		
}