#pragma once

#include <string>
#include <vector>

#include "../DeviceBase.h"
#include "../Sensor.h"
#include "../../Telemetry/Telemetry.h"

class TelemetryAgent : public DeviceBase, public Sensor
{
public:
	TelemetryAgent(
		std::string Name="Telemetery Agent",
		std::string Description="Monitoring agent for SmartShop Rasperry Devices",
		unsigned int PollingInterval=300,
		float TempWarning=50.0,
		float TempCrit=60.0,
		float DiskPctWarn=60.0,
		float DiskPctCrit=75.0,
		bool OnlyReportRootFS=true);	
	
	std::vector<SensorEvent> PollSensor() override;

private:
	float tempWarn, tempCrit, diskWarn, diskCrit;
	bool onlyRootFS;
};
	