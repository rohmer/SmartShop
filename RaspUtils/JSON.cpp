#include "JSON.h"

std::string JSON::Print(const cJSON *json)
{
	char *src = cJSON_Print(json);
	std::string ret = src;
	free(src);
	return ret;
}