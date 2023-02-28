#include "NodeAuth.h"

bool NodeAuth::IsNodeAuthorized(const httpserver::http_request &request)
{
	std::string hostid(request.get_arg(std::string("hostid")));
	if (!DEFAULT_AUTH)
	{
		return DB::GetInstance()->NodeAuthorized(hostid);
	}
	
	return true;
}