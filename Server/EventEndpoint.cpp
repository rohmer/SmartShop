#include "EventEndpoint.h"

std::shared_ptr<httpserver::http_response> EventEndpoint::render_POST(const httpserver::http_request &request)
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
	
	try
	{
		SensorEvent se = SensorEvent::FromJSON(doc);
		se.StoreToDB();
		cJSON_Delete(doc);
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("OK", 200, "text/plain"));			
	}
	catch (const std::exception&e)
	{
		Logger::GetInstance()->LogW("Error parsing event message");
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error parsing event message", 406, "text/plain"));				
	}
	
}

std::shared_ptr<httpserver::http_response> EventEndpoint::render_GET(const httpserver::http_request &request)
{		
	std::stringstream ss;
	ss << "GET from: " << request.get_requestor();
	Logger::GetInstance()->LogI(ss.str());
	try
	{	
		using namespace sqlite_orm;
		std::vector<DBEventData> evts = DB::GetInstance()->GetStorage()->get_all<DBEventData>(sqlite_orm::limit(25));
	
		cJSON *doc = cJSON_CreateObject();
		cJSON *evtMsgs = cJSON_CreateArray();
		for (std::vector<DBEventData>::iterator it = evts.begin();
			it != evts.end();
			++it)
		{
			SensorEvent evt = SensorEvent::GetFromDB(it->ID);
			cJSON_AddItemToArray(evtMsgs, evt.ToJSON());
		}
		cJSON_AddItemToObject(doc, "msgs", evtMsgs);
		std::string msgRet = cJSON_Print(doc);
		cJSON_Delete(evtMsgs);
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response(msgRet, 200, "text/plain"));			
	
	}
	catch (std::exception &e)
	{
		std::stringstream ss;
		ss << "Exception getting events, " << e.what();
		Logger::GetInstance()->LogC(ss.str());
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response(ss.str(), 406, "text/plain"));				
	}
}
