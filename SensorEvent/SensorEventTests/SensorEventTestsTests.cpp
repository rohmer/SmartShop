#include <stdio.h>
#include <sstream>
#include "../DB/DB.h"
#include "SensorEvent.h"
#include <cjson/cJSON.h>
#include <CppUTest/CommandLineTestRunner.h>
TEST_GROUP(SwitchTests)
{
};

TEST(SwitchTests, CreateSwitchEvent)
{
	SwitchData sd = SwitchData(0, true);
	CHECK(sd.GetValue() == true);
	CHECK(sd.GetSwitchID() == 0);
}

TEST(SwitchTests, ToJSON)
{
	SwitchData sd = SwitchData(1, false);
	cJSON *doc = sd.ToJSON();

	
	CHECK(cJSON_HasObjectItem(doc,"id"));
	CHECK(cJSON_GetObjectItem(doc,"id")->valueint == 1);
	CHECK(cJSON_HasObjectItem(doc,"value"));
	CHECK(cJSON_GetObjectItem(doc, "value")->valueint == false);
	CHECK(cJSON_HasObjectItem(doc,"type"));
	CHECK(cJSON_GetObjectItem(doc,"type")->valueint == eSensorDataTypes::SWITCH);
}

TEST(SwitchTests, FromJSON)
{
	cJSON *doc;
	std::stringstream json;
	json << "{\"id\":0,\"type\":" << eSensorDataTypes::SWITCH << ",\"value\": true}";
	doc=cJSON_Parse(json.str().c_str());
	SwitchData sd = SwitchData::FromJSON(doc);
	CHECK(sd.GetSwitchID() == 0);
	CHECK(sd.GetValue() == true);
	CHECK(sd.GetDataType() == eSensorDataTypes::SWITCH);
}

TEST_GROUP(VectorTests)
{
};

TEST(VectorTests, CreateVectorTest)
{
	VectorData vd(1, 2, 3, 4, 5, 6);
	CHECK(vd.GetX() == 1);
	CHECK(vd.GetY() == 2);
	CHECK(vd.GetZ() == 3);
	CHECK(vd.GetRoll() == 4);
	CHECK(vd.GetHeading() == 5);
	CHECK(vd.GetPitch() == 6);
}

TEST(VectorTests, ToJSON)
{
	VectorData vd(1, 2, 3, 4, 5, 6);
	cJSON *json = vd.ToJSON();
	CHECK(cJSON_HasObjectItem(json, "x"));
	CHECK(cJSON_GetObjectItem(json, "x")->valuedouble == 1);	
	CHECK(cJSON_HasObjectItem(json, "y"));
	CHECK(cJSON_GetObjectItem(json, "y")->valuedouble == 2);
	CHECK(cJSON_HasObjectItem(json, "z"));
	CHECK(cJSON_GetObjectItem(json, "z")->valuedouble == 3);
	
	CHECK(cJSON_HasObjectItem(json, "roll"));
	CHECK(cJSON_GetObjectItem(json, "roll")->valuedouble == 4);
	CHECK(cJSON_HasObjectItem(json, "heading"));
	CHECK(cJSON_GetObjectItem(json, "heading")->valuedouble == 5);
	CHECK(cJSON_HasObjectItem(json, "pitch"));
	CHECK(cJSON_GetObjectItem(json, "pitch")->valuedouble == 6);
}

TEST(VectorTests, FromJSON)
{
	std::stringstream ss;
	ss << "{\"type\":" << eSensorDataTypes::COLOR << ",\"x\": 1,\"y\": 2,\"z\": 3,\"roll\": 4,\"heading\":5, \"pitch\":6 }";
	
	
	cJSON *json = cJSON_Parse(ss.str().c_str());
	VectorData vd = VectorData::FromJSON(json);
	
	CHECK(vd.GetX() == 1);
	CHECK(vd.GetY() == 2);
	CHECK(vd.GetZ() == 3);
	CHECK(vd.GetRoll() == 4);
	CHECK(vd.GetHeading() == 5);
	CHECK(vd.GetPitch() == 6);
	CHECK(vd.GetDataType() == eSensorDataTypes::VECTOR);
}

TEST_GROUP(ColorTests)
{
};

TEST(ColorTests, CreateColorTest)
{
	ColorData cd(1, 2, 3, 4);
	CHECK(cd.GetRed() == 1);
	CHECK(cd.GetGreen() == 2);
	CHECK(cd.GetBlue() == 3);
	CHECK(cd.GetAlpha() == 4);
}

TEST(ColorTests, ToJSON)
{
	ColorData cd(1, 2, 3, 4);
	cJSON *json = cd.ToJSON();
	CHECK(cJSON_HasObjectItem(json, "r"));
	CHECK(cJSON_GetObjectItem(json, "r")->valuedouble == 1);
	CHECK(cJSON_HasObjectItem(json, "g"));
	CHECK(cJSON_GetObjectItem(json, "g")->valuedouble == 2);
	CHECK(cJSON_HasObjectItem(json, "b"));
	CHECK(cJSON_GetObjectItem(json, "b")->valuedouble == 3);
	CHECK(cJSON_HasObjectItem(json, "a"));
	CHECK(cJSON_GetObjectItem(json, "a")->valuedouble == 4);
}

TEST(ColorTests, FromJSON)
{
	std::stringstream ss;
	ss << "{\"type\":" << eSensorDataTypes::COLOR << ",\"r\": 1,\"g\": 2,\"b\": 3,\"a\": 4 }";
	cJSON *json = cJSON_Parse(ss.str().c_str());
	ColorData cd = ColorData::FromJSON(json);
	CHECK(cd.GetRed() == 1);
	CHECK(cd.GetGreen() == 2);
	CHECK(cd.GetBlue() == 3);
	CHECK(cd.GetAlpha() == 4);
	CHECK(cd.GetDataType() == eSensorDataTypes::COLOR);
}

TEST_GROUP(IntTests)
{
};

TEST(IntTests, CreateIntTest)
{
	IntData id("testVal", 1234);
	CHECK(id.GetDataType() == eSensorDataTypes::INTEGER);
	CHECK(id.GetName() == "testVal");
	CHECK(id.GetValue() == 1234);
}

TEST(IntTests, ToJSON)
{
	IntData id("testVal", 1234);
	cJSON *json = id.ToJSON();
	CHECK(cJSON_HasObjectItem(json, "name"));
	std::string name = cJSON_GetObjectItem(json, "name")->valuestring;
	STRCMP_EQUAL(name.c_str(),"testVal");
	CHECK(cJSON_HasObjectItem(json, "value"));
	CHECK(cJSON_GetObjectItem(json, "value")->valueint == 1234);
	CHECK(cJSON_HasObjectItem(json, "type"));
	CHECK(cJSON_GetObjectItem(json, "type")->valueint == eSensorDataTypes::INTEGER);
}

TEST(IntTests, FromJSON)
{
	std::stringstream ss;
	ss << "{\"type\":" << eSensorDataTypes::INTEGER << ",\"name\": \"testVal\", \"value\": 42 }";
	cJSON *json = cJSON_Parse(ss.str().c_str());
	IntData id = IntData::FromJSON(json);
	CHECK(id.GetDataType() == eSensorDataTypes::INTEGER);
	std::string name = id.GetName();
	STRCMP_EQUAL(name.c_str(),"testVal");
	CHECK(id.GetValue() == 42);
}

TEST_GROUP(FloatTests)
{
}
;

TEST(FloatTests, CreateFloatTest)
{
	FloatData id("testVal", 1234.5);
	CHECK(id.GetDataType() == eSensorDataTypes::FLOAT);
	CHECK(id.GetName() == "testVal");
	CHECK(id.GetValue() == 1234.5);
}

TEST(FloatTests, ToJSON)
{
	FloatData id("testVal", 1234.5);
	cJSON *json = id.ToJSON();
	CHECK(cJSON_HasObjectItem(json, "name"));
	std::string name = cJSON_GetObjectItem(json, "name")->valuestring;
	STRCMP_EQUAL(name.c_str(), "testVal");
	CHECK(cJSON_HasObjectItem(json, "value"));
	CHECK(cJSON_GetObjectItem(json, "value")->valuedouble == 1234.5);
	CHECK(cJSON_HasObjectItem(json, "type"));
	CHECK(cJSON_GetObjectItem(json, "type")->valueint == eSensorDataTypes::FLOAT);
}

TEST(FloatTests, FromJSON)
{
	std::stringstream ss;
	ss << "{\"type\":" << eSensorDataTypes::FLOAT << ",\"name\": \"testVal\", \"value\": 42.24 }";
	cJSON *json = cJSON_Parse(ss.str().c_str());
	FloatData id = FloatData::FromJSON(json);
	CHECK(id.GetDataType() == eSensorDataTypes::FLOAT);
	std::string name = id.GetName();
	STRCMP_EQUAL(name.c_str(), "testVal");
	CHECK(abs(id.GetValue() - 42.24f)<0.00001f);
}

TEST_GROUP(StringTests)
{
}
;

TEST(StringTests, CreateStringTest)
{
	StringData id("testVal", "abc123");
	CHECK(id.GetDataType() == eSensorDataTypes::STRING);
	CHECK(id.GetName() == "testVal");
	STRCMP_EQUAL(id.GetValue().c_str(), "abc123");
}

TEST(StringTests, ToJSON)
{
	StringData id("testVal", "abc123");
	cJSON *json = id.ToJSON();
	CHECK(cJSON_HasObjectItem(json, "name"));
	std::string name = cJSON_GetObjectItem(json, "name")->valuestring;
	STRCMP_EQUAL(name.c_str(), "testVal");
	CHECK(cJSON_HasObjectItem(json, "value"));
	std::string v = cJSON_GetObjectItem(json, "value")->valuestring;
	
	STRCMP_EQUAL(v.c_str(),"abc123");
	CHECK(cJSON_HasObjectItem(json, "type"));
	CHECK(cJSON_GetObjectItem(json, "type")->valueint == eSensorDataTypes::STRING);
}

TEST(StringTests, FromJSON)
{
	std::stringstream ss;
	ss << "{\"type\":" << eSensorDataTypes::FLOAT << ",\"name\": \"testVal\", \"value\": \"abc123\" }";
	cJSON *json = cJSON_Parse(ss.str().c_str());
	StringData id = StringData::FromJSON(json);
	CHECK(id.GetDataType() == eSensorDataTypes::STRING);
	std::string name = id.GetName();
	STRCMP_EQUAL(name.c_str(), "testVal");
	STRCMP_EQUAL(id.GetValue().c_str(), "abc123");
}

TEST_GROUP(DBTests)
{
};

TEST(DBTests, IntTest)
{
	DB::GetInstance("SmartShop.db");
	IntData id("IntData", 1234L);
	id.StoreToDB(1);
}

TEST(DBTests, StrTest)
{
	DB::GetInstance("SmartShop.db");
	StringData sd("StringData", "Test");
	sd.StoreToDB(2);
}

TEST(DBTests, FloatTest)
{
	DB::GetInstance("SmartShop.db");
	FloatData fd("FloatData", 0.123f);
	fd.StoreToDB(3);
}

TEST(DBTests, ColorTest)
{
	DB::GetInstance("SmartShop.db");
	ColorData cd(1.0f, 1.0f, 1.0f, 1.0f);
	cd.StoreToDB(4);
}

TEST(DBTests, SwitchTest)
{
	DB::GetInstance("SmartShop.db");
	SwitchData sd(1, true);
	sd.StoreToDB(5);
}

TEST(DBTests, VectorTest)
{
	DB::GetInstance("SmartShop.db");
	VectorData vd(1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f);
	vd.StoreToDB(6);
}

