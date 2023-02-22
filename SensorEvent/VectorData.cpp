#include "VectorData.h"

VectorData::VectorData(float X, float Y, float Z, float Roll, float Heading, float Pitch)
	: SensorDataBase(eSensorDataTypes::VECTOR)
	, x(X)
	, y(Y)
	, z(Z)
	, roll(Roll)
	, pitch(Pitch)
	, heading(Heading)
{
}

cJSON *VectorData::ToJSON()
{
	cJSON *ret = cJSON_CreateObject();
	cJSON *ctype = cJSON_CreateNumber(dataType);
	cJSON *jx = cJSON_CreateNumber(x);
	cJSON *jy = cJSON_CreateNumber(y);
	cJSON *jz = cJSON_CreateNumber(z);
	cJSON *jroll = cJSON_CreateNumber(roll);
	cJSON *jpitch = cJSON_CreateNumber(pitch);
	cJSON *jheading = cJSON_CreateNumber(heading);

	cJSON_AddItemToObject(ret, "type", ctype);
	cJSON_AddItemToObject(ret, "x", jx);
	cJSON_AddItemToObject(ret, "y", jy);
	cJSON_AddItemToObject(ret, "z", jz);
	cJSON_AddItemToObject(ret, "heading", jheading);
	cJSON_AddItemToObject(ret, "pitch", jpitch);
	cJSON_AddItemToObject(ret, "roll", jroll);
	return ret;
}	

VectorData *VectorData::FromJSON(cJSON *json)
{
	float jX = 0, jY = 0, jZ = 0, jRoll = 0, jPitch = 0, jHeading = 0;
	if (cJSON_HasObjectItem(json, "x"))
	{
		jX = cJSON_GetObjectItem(json, "x")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "y"))
	{
		jY = cJSON_GetObjectItem(json, "y")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "z"))
	{
		jZ = cJSON_GetObjectItem(json, "z")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "roll"))
	{
		jRoll = cJSON_GetObjectItem(json, "roll")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "pitch"))
	{
		jPitch = cJSON_GetObjectItem(json, "pitch")->valuedouble;
	}
	if (cJSON_HasObjectItem(json, "heading"))
	{
		jHeading = cJSON_GetObjectItem(json, "heading")->valuedouble;
	}
	
	return new VectorData(jX, jY, jZ, jRoll, jHeading, jPitch);
}

void VectorData::StoreToDB(unsigned long eventID)
{
	DBVectorData dbo;
	dbo.EventID = eventID;
	dbo.Heading = heading;
	dbo.Pitch = pitch;
	dbo.Roll = roll;
	dbo.X = x;
	dbo.Y = y;
	dbo.Z = z;
	DB::GetInstance()->GetStorage()->insert(dbo);
}