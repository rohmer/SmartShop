#include "LogEndpoint.h"

std::shared_ptr<httpserver::http_response> LogEndpoint::render_POST(const httpserver::http_request &request)
{	
	std::string body(request.get_content());
	std::stringstream ss;
	ss << "POST from: " << request.get_requestor();
	Logger::GetInstance()->LogI(ss.str());
	
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
	if (cJSON_HasObjectItem(doc, "hostid"))
		logmsg.HostID = cJSON_GetObjectItem(doc, "hostid")->valuestring;
	
	try
	{
		DB::GetInstance()->GetStorage()->insert(logmsg);	
	}
	catch (const std::exception &e)
	{
		std::stringstream ss;
		ss << "Error inserting into DB, " << e.what();
		Logger::GetInstance()->LogC(ss.str());
		return std::shared_ptr<httpserver::string_response>(new httpserver::string_response(ss.str(), 500));
	}
	return std::shared_ptr<httpserver::string_response>(new httpserver::string_response("OK", 200, "text/plain"));
}

std::shared_ptr<httpserver::http_response> LogEndpoint::render_GET(const httpserver::http_request &request)
{		
	std::stringstream ss;
	ss << "GET from: " << request.get_requestor();
	Logger::GetInstance()->LogI(ss.str());
	std::vector<LogMsg> msgs = DB::GetInstance()->GetStorage()->get_all<LogMsg>(sqlite_orm::limit(25));
	cJSON *doc = cJSON_CreateObject();
	cJSON *logmsgs = cJSON_CreateArray();
	for (std::vector<LogMsg>::iterator it = msgs.begin();
		it != msgs.end();
		++it)
	{
		cJSON *msgJson = cJSON_CreateObject();
		cJSON_AddItemToObject(msgJson, "ID", cJSON_CreateNumber(it->ID));
		cJSON_AddItemToObject(msgJson, "host", cJSON_CreateString(it->Host.c_str()));
		std::string sevStr = "INFO";
		switch (it->Severity)
		{
		case 0:
			sevStr = "INFO";
			break;
		case 1:
			sevStr = "WARN";
			break;
		case 2:
			sevStr = "CRIT";
			break;
		default:
			sevStr = "UNK";
			break;			
		}
		cJSON_AddItemToObject(msgJson, "sev", cJSON_CreateString(sevStr.c_str()));
		
		date::sys_seconds tp{std::chrono::seconds{it->Timestamp}};		
		std::string timeStr = date::format("%Y-%m-%d %I:%M:%S %p", tp);
		cJSON_AddItemToObject(msgJson, "time", cJSON_CreateString(timeStr.c_str()));
		cJSON_AddItemToArray(logmsgs, msgJson);
	}
	cJSON_AddItemToObject(doc, "msgs", logmsgs);
	std::string msgRet = cJSON_Print(logmsgs);
	cJSON_Delete(logmsgs);		
	
	return std::shared_ptr<httpserver::string_response>(new httpserver::string_response(msgRet, 200, "text/plain"));
}