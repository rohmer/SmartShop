#pragma once
#include <cstring>
#include <sstream>
#include <string>
#include "cJSON.h"

enum eConfigDataType
{
	C_BOOL=0,
	C_LONG=1,
	C_STR=3,
	C_FLOAT=4
};

class DeviceConfigItem
{
public:
	DeviceConfigItem()
	{
	}
	
	DeviceConfigItem(std::string name, const char value[], bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		std::stringstream ss;
		ss << value;
		SetValue(ss.str());		
	}
	
	DeviceConfigItem(std::string name, int value, bool readOnly = false) 
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}
		
	DeviceConfigItem(std::string name, bool value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}
	
	DeviceConfigItem(std::string name, float value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, long value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, std::string value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	eConfigDataType GetDataType()
	{
		return dataType;
	}

	void SetValue(int val)
	{
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_LONG;
	}
	
	void SetValue(long val)
	{
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_LONG;
	}
	
	void SetValue(float val)
	{
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_FLOAT;
	}
	
	void SetValue(std::string val)
	{
		value = val;
		dataType = eConfigDataType::C_STR;
	}
	
	void SetValue(bool val)
	{
		if (val)
			value = "1";
		else 
			value = "0";
	
		dataType = eConfigDataType::C_BOOL;
	}
	
	std::string GetStringVal()
	{
		return value;	
	}
	
	bool GetBoolVal()
	{
		if (strcmp(value.c_str(), "1")==0)
			return true;
		return false;
	}
	
	float GetFloatVal()
	{
		return std::atof(value.c_str());
	}
	
	long GetLongVal()
	{
		return std::atof(value.c_str());
	}
	
	bool IsReadOnly()
	{
		return readOnly;
	}
		
	std::string GetName()
	{
		return name;
	}
	
	cJSON *ToJSON()
	{
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToObject(obj, "name", cJSON_CreateString(name.c_str()));
		cJSON_AddItemToObject(obj, "value", cJSON_CreateString(value.c_str()));
		cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(readOnly));
		cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(dataType));
		return obj;		
	}
	
	static DeviceConfigItem FromJSON(cJSON *obj)
	{
		std::string name="", value="";
		eConfigDataType dataType = C_STR;
		bool ro = false;
		
		if (cJSON_HasObjectItem(obj, "name"))
		{
			name = cJSON_GetObjectItem(obj, "name")->valuestring;			
		}
		if (cJSON_HasObjectItem(obj, "value"))
		{
			value = cJSON_GetObjectItem(obj, "value")->valuestring;			
		}
		if (cJSON_HasObjectItem(obj, "ro"))
		{
			ro = cJSON_IsTrue(cJSON_GetObjectItem(obj, "ro"));
		}
		if (cJSON_HasObjectItem(obj, "value"))
		{
			value = cJSON_GetObjectItem(obj, "value")->valuestring;			
		}
		if (cJSON_HasObjectItem(obj, "dataType"))
		{
			dataType = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
		}
		switch (dataType)
		{
		case C_LONG:
			{
				long v = std::atol(value.c_str());
				return DeviceConfigItem(name, v, ro);
			}
		case C_BOOL:
			{
				bool v = false;
				if (strcmp(value.c_str(), "1") == 0)
					v = true;
				return DeviceConfigItem(name, v, ro);
			}
		case C_FLOAT:
			{
				float v = std::atof(value.c_str());
				return DeviceConfigItem(name, v, ro);
			}
		default:
			return DeviceConfigItem(name, value, ro);
		}
	}
	
private:
	std::string name;
	bool readOnly;
	std::string value;
	eConfigDataType dataType;	
};


