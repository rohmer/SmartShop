#pragma once
#include <cstring>
#include <climits>
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
	
	DeviceConfigItem(std::string name, const char value[], bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
	{
		std::stringstream ss;
		ss << value;
		SetValue(ss.str());		
	}
	
	DeviceConfigItem(std::string name, std::string value, bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
		, value(value)
	{
	}
	
	DeviceConfigItem(std::string name, 
		int value, 
		int minValue=std::numeric_limits<int>::min(), 
		int maxValue=std::numeric_limits<int>::max(),
		bool readOnly = false) 
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
	
	DeviceConfigItem(
		std::string name, 
		float value, 
		float minValue=std::numeric_limits<float>::min(), 
		float maxValue=std::numeric_limits<float>::max(), 
		float stepValue=0,
		bool readOnly = false)
		: name(name)
		, floatMin(minValue)
		, floatMax(maxValue)
		, floatStep(stepValue)
		, readOnly(readOnly)
	{
		SetValue(value);
	}

	DeviceConfigItem(std::string name, 
		long value,
		long minValue=std::numeric_limits<long>::min(),
		long maxValue=std::numeric_limits<long>::max(),
		long stepValue=0,
		bool readOnly = false)
		: name(name)
		, readOnly(readOnly)
		, longMin(minValue)
		, longMax(maxValue)
		, longStep(stepValue)
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
	
	float GetFloatMax()
	{
		return floatMax;
	}
	void SetFloatMax(float v)
	{
		floatMax = v;
	}
	float GetFloatMin()
	{
		return floatMin;
	}
	void SetFloatMin(float v)
	{
		floatMin = v;
	}
	float GetFloatStep()
	{
		return floatStep;
	}
	void SetFloatStep(float v)
	{
		floatStep = v;
	}
	long GetLongMax()
	{
		return longMax;
	}
	void SetLongMax(long v)
	{
		longMax = v;
	}
	long GetLongMin()
	{
		return longMin;
	}
	void SetLongMin(long v)
	{
		longMin = v;
	}
	long GetLongStep()
	{
		return longStep;
	}
	void SetLongStep(long v)
	{
		longStep = v;
	}
	
	std::vector<std::string> GetLegalStringValues()
	{
		return legalValues;
	}
	
	cJSON *ToJSON()
	{
		cJSON *obj = cJSON_CreateObject();
		cJSON_AddItemToObject(obj, "name", cJSON_CreateString(name.c_str()));
		if(dataType!=eConfigDataType::C_ARRAY)
			cJSON_AddItemToObject(obj, "value", cJSON_CreateString(value.c_str()));
		cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(readOnly));
		cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(dataType));
		
		switch (dataType)
		{
		case eConfigDataType::C_ARRAY:
			{
				cJSON *arr = cJSON_CreateArray();
				for (int i = 0; i < arrayValues.size(); i++)
					cJSON_AddItemToArray(arr, arrayValues[i].ToJSON());
				cJSON_AddItemToObject(obj, "value", arr);
			}
			break;
		case eConfigDataType::C_BOOL:
			break;
		case eConfigDataType::C_FLOAT:
			{
				if (floatMax != std::numeric_limits<float>::max())
					cJSON_AddItemToObject(obj, "max", cJSON_CreateNumber(floatMax));
				if (floatMin != std::numeric_limits<float>::min())
					cJSON_AddItemToObject(obj, "min", cJSON_CreateNumber(floatMin));
				if (floatStep != 0)
					cJSON_AddItemToObject(obj, "step", cJSON_CreateNumber(floatStep));
			}
			break;
		case eConfigDataType::C_LONG:
			{
				if (longMax != std::numeric_limits<long>::max())
					cJSON_AddItemToObject(obj, "max", cJSON_CreateNumber(longMax));
				if (longMin != std::numeric_limits<long>::min())
					cJSON_AddItemToObject(obj, "min", cJSON_CreateNumber(longMin));
				if (longStep != 0)
					cJSON_AddItemToObject(obj, "step", cJSON_CreateNumber(longStep));
			}
			break;
		case eConfigDataType::C_STR:
			{
				if (legalValues.size() > 0)
				{
					cJSON *arr = cJSON_CreateArray();
					for (int i = 0; i < legalValues.size(); i++)
						cJSON_AddItemToArray(arr, cJSON_CreateString(legalValues[i].c_str()));
					cJSON_AddItemToObject(obj, "legalValues", arr);
				}
			}
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
				long max = LONG_MAX, min = LONG_MIN;
				long longStep = 0;
				if (cJSON_HasObjectItem(obj,"max"))
				{
					max = cJSON_GetObjectItem(obj, "max")->valueint;
				}
				if (cJSON_HasObjectItem(obj, "min"))
				{
					min = cJSON_GetObjectItem(obj, "min")->valueint;
				}
				if (cJSON_HasObjectItem(obj, "step"))
				{
					longStep = cJSON_GetObjectItem(obj, "step")->valueint;
				}
				return DeviceConfigItem(name, (long)v, min,max,longStep,ro);
			}
			break;
		case C_BOOL:
			{
				bool v = false;
				if (strcmp(value.c_str(), "1") == 0)
					v = true;
				return DeviceConfigItem(name, v, ro);
			}
			break;
		case C_FLOAT:
			{
				float v = std::atof(value.c_str());
				float max = std::numeric_limits<float>::max(), min = std::numeric_limits<float>::min();
				float floatStep = 0;
				if (cJSON_HasObjectItem(obj, "max"))
				{
					max = cJSON_GetObjectItem(obj, "max")->valuedouble;
				}
				if (cJSON_HasObjectItem(obj, "min"))
				{
					min = cJSON_GetObjectItem(obj, "min")->valuedouble;
				}
				if (cJSON_HasObjectItem(obj, "step"))
				{
					floatStep = cJSON_GetObjectItem(obj, "step")->valuedouble;
				}
				return DeviceConfigItem(name, v, min, max, floatStep, ro);
			}
			break;
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
			break;
		case C_STR:
			{
				if (cJSON_HasObjectItem(obj, "legalValues"))
				{
					cJSON *arr = cJSON_GetObjectItem(obj, "legalValues");
					std::vector<std::string> lvalues;
					if (cJSON_IsArray(arr))
					{						
						cJSON *itr;
						cJSON_ArrayForEach(itr, arr)
						{
							lvalues.push_back(itr->valuestring);
						}
					}
					return DeviceConfigItem(name, value, lvalues, ro);
				}
			}
		}
	}
	
private:
	float floatMin=std::numeric_limits<float>::min(), floatMax=std::numeric_limits<float>::max();
	float floatStep = 0;
	long longMin=std::numeric_limits<long>::min(), longMax=std::numeric_limits<long>::max();
	long longStep = 0;
	std::vector<std::string> legalValues;
	std::string name;
	bool readOnly;
	std::string value;
	eConfigDataType dataType;	
	std::vector<DeviceConfigItem> arrayValues;
};


