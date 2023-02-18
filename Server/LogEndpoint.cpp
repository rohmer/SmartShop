#include "LogEndpoint.h"

std::shared_ptr<httpserver::http_response> LogEndpoint::render_POST(const httpserver::http_request &);
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
	response.send(Http::Code::Ok);
}