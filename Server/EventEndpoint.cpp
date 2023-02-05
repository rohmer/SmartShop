#include "EventEndpoint.h"

Pistache::Rest::Route::Result  EventEndpoint::ExecEventEndpoint(const Rest::Request &request, Http::ResponseWriter response)
{
	std::string body = request.body();
	
	cJSON *doc;
	try
	{
		doc = cJSON_Parse(body.c_str());
	}
	catch (const std::exception&)
	{
		Logger::GetInstance()->LogW("Error parsing event message");
		response.send(Http::Code::Not_Acceptable);
		return Rest::Route::Result::Failure;
	}
	
	try
	{
		SensorEvent se = SensorEvent::FromJSON(doc);
		se.StoreToDB();
		response.send(Http::Code::Ok);
		return Rest::Route::Result::Ok;
	}
	catch (const std::exception&e)
	{
		Logger::GetInstance()->LogW("Error parsing event message");
		response.send(Http::Code::Not_Acceptable);
		return Rest::Route::Result::Failure;
	}
	
}