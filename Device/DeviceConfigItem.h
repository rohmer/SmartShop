#pragma once
#include <cstring>
#include <sstream>
#include <string>
#include "cJSON.h"

enum eConfigDataType
{
	C_BOOL = 0,
	C_LONG = 1,
	C_STR = 3,
	C_FLOAT = 4,
	C_ARRAY = 5
};

class DeviceConfigItem
{
public:
	DeviceConfigItem()
	{
	}
	
	DeviceConfigItem(std::string name, const char value[], std::vector<std::string> validValues, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
		,legalValues(validValues)
	{
		std::stringstream ss;
		ss << value;
		SetValue(ss.str());		
	}
	
	DeviceConfigItem(std::string name, int value, int minValue=INT32_MIN, int maxValue=INT32_MAX, bool readOnly = false) 
		: name(name)
		, readOnly(readOnly)
		, longMax(maxValue)
		, longMin(minValue)
	{
		SetValue(value);
	}
		
	DeviceConfigItem(std::string name, bool value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}
	
	DeviceConfigItem(std::string name, float value, float minValue=std::numeric_limits<float>::min(), float maxValue=std::numeric_limits<float>::max(), bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, 
		long value,
		long minValue=std::numeric_limits<long>::min(),
		long maxValue=std::numeric_limits<long>::max(),
		bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, std::string value, std::vector<std::string> legalValues, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
		, legalValues(legalValues)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, std::vector<DeviceConfigItem> value, bool readOnly = false)
	{
		for (int i = 0; i < value.size(); i++)
			arrayValues.push_back(value[i]);
	}
	
	eConfigDataType GetDataType()
	{
		return dataType;
	}

	void SetValue(int val)
	{
		if (val > longMax)
			val = longMax;
		if (val < longMin)
			val = longMin;
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_LONG;
	}
	
	void SetValue(long val)
	{
		if (val > longMax)
			val = longMax;
		if (val < longMin)
			val = longMin;
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_LONG;
	}
	
	void SetValue(float val)
	{
		if (val < floatMin)
			val = floatMin;
		if (val > floatMax)
			val = floatMax;
		
		std::stringstream ss;
		ss << val;
		value = ss.str();
		dataType = eConfigDataType::C_FLOAT;
	}
	
	void SetValue(std::string val)
	{
		bool legal = false;
		if (legalValues.size() > 0)
		{
			for (int i = 0; i < legalValues.size(); i++)
				if (std::strcmp(legalValues[i].c_str(), val.c_str()) == 0)
				{
					legal = true;
					break;
				}
		}
		if (legal)
		{
			value = val;
			dataType = eConfigDataType::C_STR;
		 }
	}
	
	void SetValue(bool val)
	{
		if (val)
			value = "1";
		else 
			value = "0";
	
		dataType = eConfigDataType::C_BOOL;
	}
	
	void AddArrayItem(DeviceConfigItem dci)
	{
		if (dataType == eConfigDataType::C_ARRAY)
			arrayValues.push_back(dci);
	}
	
	void ClearArrayItems()
	{
		if (dataType == eConfigDataType::C_ARRAY)
			arrayValues.clear();
	}
	
	std::vector<DeviceConfigItem> GetArrayValues()
	{
		return arrayValues;
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
		if(dataType!=eConfigDataType::C_ARRAY)
			cJSON_AddItemToObject(obj, "value", cJSON_CreateString(value.c_str()));
		cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(readOnly));
		cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(dataType));
		if (dataType == eConfigDataType::C_ARRAY)
		{
			cJSON *arr = cJSON_CreateArray();
			for (int i = 0; i < arrayValues.size(); i++)
				cJSON_AddItemToArray(arr, arrayValues[i].ToJSON());
			cJSON_AddItemToObject(obj, "value", arr);
		}
		
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
		if (cJSON_HasObjectItem(obj, "dataType"))
		{
			dataType = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
		}
		if (cJSON_HasObjectItem(obj, "value") && dataType!=eConfigDataType::C_ARRAY)
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
		case C_ARRAY:
			{
				if (cJSON_HasObjectItem(obj, "value"))
				{
					cJSON *arr = cJSON_GetObjectItem(obj, "value");
					if (cJSON_IsArray(arr))
					{
						std::vector<DeviceConfigItem> dcis;
						cJSON *itr = cJSON_CreateObject();
						cJSON_ArrayForEach(itr, arr)
						{
							dcis.push_back(DeviceConfigItem::FromJSON(itr));
						}
						return DeviceConfigItem(name, dcis, ro);
					}
				}
			}
		default:
			return DeviceConfigItem(name, value, ro);
		}
	}
	
private:
	float floatMin, floatMax;
	long longMin, longMax;
	std::vector<std::string> legalValues;
	std::string name;
	bool readOnly;
	std::string value;
	eConfigDataType dataType;	
	std::vector<DeviceConfigItem> arrayValues;
};


