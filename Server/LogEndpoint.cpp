#include "LogEndpoint.h"

std::shared_ptr<httpserver::http_response> LogEndpoint::render_POST(const httpserver::http_request &request)
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
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("Error parsing log message", 406, "text/plain"));
	}
	
	LogMsg logmsg;
	if (cJSON_HasObjectItem(doc,"host"))
		logmsg.Host = cJSON_GetObjectItem(doc,"host")->valuestring;
	if (cJSON_HasObjectItem(doc,"sev"))
		logmsg.Severity = cJSON_GetObjectItem(doc,"sev")->valueint;
	if (cJSON_HasObjectItem(doc, "msg"))
		logmsg.Message = cJSON_GetObjectItem(doc,"msg")->valuestring;
	if (cJSON_HasObjectItem(doc, "time"))
		logmsg.Timestamp = cJSON_GetObjectItem(doc, "time")->valueint;
	else
		logmsg.Timestamp = time(NULL);
	DB::GetInstance()->GetStorage()->insert(logmsg);
	return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("OK", 200, "text/plain"));
}