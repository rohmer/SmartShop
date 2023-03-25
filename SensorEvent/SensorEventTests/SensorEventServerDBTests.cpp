#include <filesystem>
#include <stdio.h>
#include <sstream>
#include "../DB/DB.h"
#include "SensorEvent.h"
#include "cJSON.h"
#include "JSON.h"
#include "../Device/TelemetryAgent/TelemetryAgent.h"
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(SensorEventDBTests)
{
};

TEST(SensorEventDBTests, EventGroupsStore)
{
	Sensor *ta = dynamic_cast<Sensor *>(new TelemetryAgent("TestTelemetry", "", 3));
	std::vector<SensorEvent> events = ta->PollSensor();	
	SensorEvent::StoreGroupToDB(events);		
}

TEST(SensorEventDBTests, EventGroupsGetGroup)
{
	DB::GetInstance();
	Sensor *ta = dynamic_cast<Sensor *>(new TelemetryAgent("TestTelemetry", "", 3));
	std::vector<SensorEvent> events = ta->PollSensor();	
	if (events.size() == 0)
	{
		FAIL("Events should never be 0 size");
	}
	std::string hostname = events[0].GetHostname();
	unsigned long firstID=SensorEvent::StoreGroupToDB(events);		
	std::this_thread::sleep_for(std::chrono::seconds(2));
	events = ta->PollSensor();
	unsigned long secondID = SensorEvent::StoreGroupToDB(events);
	std::vector<SensorEvent> dbEvt = SensorEvent::GetLatestGroupFromDB(hostname, "TestTelemetry");
	if (dbEvt.size() == 0)
	{
		FAIL("Group retreived was 0 size");
	}
	CHECK_EQUAL(dbEvt.size(), events.size());
	for (int i = 0; i < dbEvt.size(); i++)
		CHECK_EQUAL(dbEvt[i].GetGroupID(), secondID);
}