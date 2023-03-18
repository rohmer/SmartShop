#pragma once

#include <string>
#include "cJSON.h"
#include "DB.h"

enum eSensorDataTypes
{
	SWITCH = 0,
	VECTOR = 1,
	COLOR = 2,
	INTEGER = 3,
	FLOAT = 4,
	STRING = 5,
	BINARY = 6,
	UNKNOWN_TYPE = 99
};

class SensorDataBase
{
public:
	SensorDataBase(eSensorDataTypes dataType)
	{
		this->dataType = dataType;
	}
	
	eSensorDataTypes GetDataType(cJSON *json)
	{
		if (cJSON_HasObjectItem(json,"type"))
		{
			switch (cJSON_GetObjectItem(json,"type")->valueint)
			{
			case 0:
				return SWITCH;
			case 1:
				return VECTOR;
			case 2:
				return COLOR;
			case 3:
				return INTEGER;
			case 4:
				return FLOAT;
			case 5:
				return STRING;
			case 6:
				return BINARY;
			default:
				return UNKNOWN_TYPE;
			}
		}
		return UNKNOWN_TYPE;
	}
	
	eSensorDataTypes GetDataType()
	{
		return dataType;
	}
	
	
protected:
	eSensorDataTypes dataType;
};