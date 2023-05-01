#include <stdio.h>
#include "../DeviceConfig.h"
#include "../DeviceConfigItem.h"
#include <CppUTest/CommandLineTestRunner.h>
#include "../RaspUtils/JSON.h"

/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

TEST_GROUP(DeviceConfig)
{
};

TEST(DeviceConfig, Create1)
{
	DeviceConfig dc("Name", "Desc", eDeviceBus::GPIO, eDeviceType::GENERIC);
	STRCMP_EQUAL("Name", dc.GetName().c_str());
	STRCMP_EQUAL("Desc", dc.GetDescription().c_str());
	CHECK(dc.GetDeviceBus() == eDeviceBus::GPIO);
	CHECK(dc.GetDeviceType() == eDeviceType::GENERIC);
}

TEST(DeviceConfig, Create2)
{
	std::vector<DeviceConfigItem> items;
	items.push_back(DeviceConfigItem("string", "string", false));
	items.push_back(DeviceConfigItem("long", 123, 0, 500, true));
	items.push_back(DeviceConfigItem("bool", true, true));
	items.push_back(DeviceConfigItem("float", 123.12, 0,500,true));
	DeviceConfig dc("Name", "Desc", eDeviceBus::I2C, eDeviceType::SENSOR,items);
	STRCMP_EQUAL("Name", dc.GetName().c_str());
	STRCMP_EQUAL("Desc", dc.GetDescription().c_str());
	CHECK(dc.GetDeviceBus() == eDeviceBus::I2C);
	CHECK(dc.GetDeviceType() == eDeviceType::SENSOR);
	CHECK(dc.GetDeviceConfig().size() == 4);
	std::string json = JSON::Print(dc.ToJSON());
	std::cout << json;
}

TEST(DeviceConfig, Serialize)
{
	std::vector<DeviceConfigItem> items;
	items.push_back(DeviceConfigItem("string", "string", false));
	items.push_back(DeviceConfigItem("long", 123, 0, 500, true));
	items.push_back(DeviceConfigItem("bool", true, true));
	items.push_back(DeviceConfigItem("float", 123.12,0,500, true));
	DeviceConfig dc("Name", "Desc", eDeviceBus::I2C, eDeviceType::SENSOR, items);
	cJSON *obj = dc.ToJSON();
	std::string val = cJSON_Print(obj);
	CHECK(cJSON_HasObjectItem(obj, "name"));
	CHECK(cJSON_HasObjectItem(obj, "desc"));
	CHECK(cJSON_HasObjectItem(obj, "bus"));
	CHECK(cJSON_HasObjectItem(obj, "type"));
	STRCMP_EQUAL("Name", cJSON_GetObjectItem(obj, "name")->valuestring);
	STRCMP_EQUAL("Desc", cJSON_GetObjectItem(obj, "desc")->valuestring);
	CHECK(eDeviceBus::I2C == (eDeviceBus)cJSON_GetObjectItem(obj, "bus")->valueint);
	CHECK(eDeviceType::SENSOR == (eDeviceType)cJSON_GetObjectItem(obj, "type")->valueint);
	CHECK(cJSON_HasObjectItem(obj, "config"));
	cJSON *arr = cJSON_GetObjectItem(obj, "config");
	CHECK(cJSON_IsArray(arr));
	cJSON *item;
	cJSON_ArrayForEach(item, arr)
	{
		DeviceConfigItem dci = DeviceConfigItem::FromJSON(item);		
	}
}

TEST_GROUP(DeviceConfigItem)
{	
};

TEST(DeviceConfigItem, Create1)
{
	DeviceConfigItem strItem("str", "value", false);
	STRCMP_EQUAL("str", strItem.GetName().c_str());
	STRCMP_EQUAL("value", strItem.GetStringVal().c_str());
	CHECK(!strItem.IsReadOnly());
}

TEST(DeviceConfigItem, Create2)
{
	DeviceConfigItem item("bool", true, true);
	STRCMP_EQUAL("bool", item.GetName().c_str());
	CHECK(item.GetBoolVal());
	CHECK(item.IsReadOnly());
}

TEST(DeviceConfigItem, Create3)
{
	DeviceConfigItem item("long", 123, 0,500,true);
	STRCMP_EQUAL("long", item.GetName().c_str());
	CHECK(item.GetLongVal()==123L);
	CHECK(item.IsReadOnly());
}

TEST(DeviceConfigItem, Create4)
{
	DeviceConfigItem item("float", 123.123,0,500, true);
	STRCMP_EQUAL("float", item.GetName().c_str());
	CHECK(item.GetFloatVal()==123.123F);
	CHECK(item.IsReadOnly());
}

TEST(DeviceConfigItem, Deserialize1)
{
	DeviceConfigItem strItem("str", "value", false);
	cJSON *obj = strItem.ToJSON();	
	CHECK(cJSON_HasObjectItem(obj, "name"));
	CHECK(cJSON_HasObjectItem(obj, "value"));
	CHECK(cJSON_HasObjectItem(obj, "ro"));
	CHECK(cJSON_HasObjectItem(obj, "dataType"));
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "name")->valuestring,"str");	
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "value")->valuestring, "value");
	CHECK(!cJSON_IsTrue(cJSON_GetObjectItem(obj, "ro")));
	cJSON *test = cJSON_GetObjectItem(obj, "dataType");
	eConfigDataType cdt = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
	CHECK(cdt == eConfigDataType::C_STR);
}

TEST(DeviceConfigItem, Deserialize2)
{
	DeviceConfigItem strItem("bool", true, false);
	cJSON *obj = strItem.ToJSON();	
	CHECK(cJSON_HasObjectItem(obj, "name"));
	CHECK(cJSON_HasObjectItem(obj, "value"));
	CHECK(cJSON_HasObjectItem(obj, "ro"));
	CHECK(cJSON_HasObjectItem(obj, "dataType"));
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "name")->valuestring, "bool");	
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "value")->valuestring, "1");
	CHECK(!cJSON_IsTrue(cJSON_GetObjectItem(obj, "ro")));
	cJSON *test = cJSON_GetObjectItem(obj, "dataType");
	eConfigDataType cdt = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
	CHECK(cdt == eConfigDataType::C_BOOL);
}

TEST(DeviceConfigItem, Deserialize3)
{
	DeviceConfigItem strItem("float", 123.0,0,500, false);
	cJSON *obj = strItem.ToJSON();	
	CHECK(cJSON_HasObjectItem(obj, "name"));
	CHECK(cJSON_HasObjectItem(obj, "value"));
	CHECK(cJSON_HasObjectItem(obj, "ro"));
	CHECK(cJSON_HasObjectItem(obj, "dataType"));
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "name")->valuestring, "float");
	CHECK(std::atof(cJSON_GetObjectItem(obj,"value")->valuestring)==123.0F);
	CHECK(!cJSON_IsTrue(cJSON_GetObjectItem(obj, "ro")));
	eConfigDataType cdt = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
	CHECK(cdt == eConfigDataType::C_FLOAT);
}

TEST(DeviceConfigItem, Deserialize4)
{
	DeviceConfigItem strItem("long", 123,0,500, false);
	cJSON *obj = strItem.ToJSON();	
	CHECK(cJSON_HasObjectItem(obj, "name"));
	CHECK(cJSON_HasObjectItem(obj, "value"));
	CHECK(cJSON_HasObjectItem(obj, "ro"));
	CHECK(cJSON_HasObjectItem(obj, "dataType"));
	STRCMP_EQUAL(cJSON_GetObjectItem(obj, "name")->valuestring, "long");
	CHECK(std::atoi(cJSON_GetObjectItem(obj, "value")->valuestring) == 123);
	CHECK(!cJSON_IsTrue(cJSON_GetObjectItem(obj, "ro")));
	eConfigDataType cdt = (eConfigDataType)cJSON_GetObjectItem(obj, "dataType")->valueint;
	CHECK(cdt == eConfigDataType::C_LONG);
}

TEST(DeviceConfigItem, Serialize1)
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString("string"));
	cJSON_AddItemToObject(obj, "value", cJSON_CreateString("value"));
	cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(eConfigDataType::C_STR));
	cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(true));
	
	DeviceConfigItem dci = DeviceConfigItem::FromJSON(obj);
	STRCMP_EQUAL(dci.GetName().c_str(), "string");
	STRCMP_EQUAL(dci.GetStringVal().c_str(), "value");
	CHECK(dci.GetDataType() == eConfigDataType::C_STR);
	CHECK(dci.IsReadOnly() == true);
}

TEST(DeviceConfigItem, Serialize2)
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString("float"));
	cJSON_AddItemToObject(obj, "value", cJSON_CreateString("123.0"));
	cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(eConfigDataType::C_FLOAT));
	cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(false));
	
	DeviceConfigItem dci = DeviceConfigItem::FromJSON(obj);
	STRCMP_EQUAL(dci.GetName().c_str(), "float");
	CHECK(dci.GetFloatVal()==123.0F);
	CHECK(dci.GetDataType() == eConfigDataType::C_FLOAT);
	CHECK(dci.IsReadOnly() == false);
}

TEST(DeviceConfigItem, Serialize3)
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString("long"));
	cJSON_AddItemToObject(obj, "value", cJSON_CreateString("123"));
	cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(eConfigDataType::C_LONG));
	cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(true));
	
	DeviceConfigItem dci = DeviceConfigItem::FromJSON(obj);
	STRCMP_EQUAL(dci.GetName().c_str(), "long");
	CHECK(dci.GetLongVal() == 123);
	CHECK(dci.GetDataType() == eConfigDataType::C_LONG);
	CHECK(dci.IsReadOnly() == true);
}

TEST(DeviceConfigItem, Serialize4)
{
	cJSON *obj = cJSON_CreateObject();
	cJSON_AddItemToObject(obj, "name", cJSON_CreateString("bool"));
	cJSON_AddItemToObject(obj, "value", cJSON_CreateString("1"));
	cJSON_AddItemToObject(obj, "dataType", cJSON_CreateNumber(eConfigDataType::C_BOOL));
	cJSON_AddItemToObject(obj, "ro", cJSON_CreateBool(true));
	
	DeviceConfigItem dci = DeviceConfigItem::FromJSON(obj);
	STRCMP_EQUAL(dci.GetName().c_str(), "bool");
	CHECK(dci.GetBoolVal()==true);
	CHECK(dci.GetDataType() == eConfigDataType::C_BOOL);
	CHECK(dci.IsReadOnly() == true);
}