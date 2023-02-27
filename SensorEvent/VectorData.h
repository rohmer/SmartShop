#pragma once
#include <string>
#include <cjson/cJSON.h>
#include "SensorDataBase.h"

class VectorData : public SensorDataBase
{
public:
	VectorData(float X=0,
		float Y=0,
		float Z=0,
		float Roll=0,
		float Heading=0, 
		float Pitch=0);
	
	cJSON *ToJSON() override;
	static VectorData FromJSON(cJSON *JSON);

	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	float GetZ()
	{
		return z;
	}
	float GetRoll()
	{
		return roll;
	}
	float GetHeading()
	{
		return heading;
	}
	float GetPitch()
	{
		return pitch;
	}
	
	void SetX(float val)
	{
		x = val;
	}
	void SetY(float val)
	{
		y = val;
	}
	void SetZ(float val)
	{
		z = val;
	}
	void SetRoll(float val)
	{
		roll = val;
	}
	void SetHeading(float val)
	{
		heading = val;
	}
	void SetPitch(float val)
	{
		pitch = val;
	}
	void StoreToDB(unsigned long eventID);
	
private:
	float x, y, z, roll, heading, pitch;
};	