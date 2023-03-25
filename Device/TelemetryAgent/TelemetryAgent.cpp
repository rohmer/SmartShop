#include "TelemetryAgent.h"

TelemetryAgent::TelemetryAgent(
	std::string Name,
	std::string Description,
	unsigned int PollingInterval,
	float TempWarning,
	float TempCrit,
	float DiskPctWarn,
	float DiskPctCrit)
	: DeviceBase(Name, Description, eDeviceType::SENSOR, eDeviceBus::NA, PollingInterval)
	, tempWarn(TempWarning)
	, tempCrit(TempCrit)
	, diskWarn(DiskPctWarn)
	, diskCrit(DiskPctCrit)
{
	config.AddConfigItem(DeviceConfigItem("TempWarn", TempWarning));
	config.AddConfigItem(DeviceConfigItem("TempCrit", TempCrit));
	config.AddConfigItem(DeviceConfigItem("DiskPctWarn", DiskPctWarn));
	config.AddConfigItem(DeviceConfigItem("DiskPctCrit", DiskPctCrit));
	if (tempWarn > tempCrit)
		tempWarn = tempCrit;
	if (diskWarn > diskCrit)
		diskWarn = diskCrit;
}

std::vector<SensorEvent> TelemetryAgent::PollSensor()
{
	std::vector<SensorEvent> ret;
	sTelemetryReturn telemetry = Telemetry::GetTelemetryStats(10, 0);
	if (tempWarn != 0 && tempCrit != 0)
	{
		if (telemetry.cpu.tempC >= tempCrit) 
		{
			SensorEvent tempEvent(name);
			tempEvent.AddEventData(FloatData("CPUTemp", telemetry.cpu.tempC));
			tempEvent.AddEventData(StringData("Severity", "CRIT"));
			ret.push_back(tempEvent);
		}
		else
			if (telemetry.cpu.tempC >= tempWarn)
		{
			SensorEvent tempEvent(name);
			tempEvent.AddEventData(FloatData("CPUTemp", telemetry.cpu.tempC));
			tempEvent.AddEventData(StringData("Severity", "WARN"));
			ret.push_back(tempEvent);
		}
		else
		{
			SensorEvent tempEvent(name);
			tempEvent.AddEventData(FloatData("CPUTemp", telemetry.cpu.tempC));
			tempEvent.AddEventData(StringData("Severity", "INFO"));
			ret.push_back(tempEvent);
		}
	}
	for (std::vector<FileSystemStats>::iterator it = telemetry.fileSystems.begin();
		it != telemetry.fileSystems.end();
		++it)
	{
		float free = 100.0 - it->usedPct;
		if (free <= diskCrit)
		{
			SensorEvent diskEvent(name);
			diskEvent.AddEventData(StringData("Filesystem", it->filesystem));
			diskEvent.AddEventData(FloatData("PctFree", free));
			diskEvent.AddEventData(StringData("Severity", "CRIT"));
			ret.push_back(diskEvent);
		}
		else
		{
			if (free <= diskWarn)
			{
				SensorEvent diskEvent(name);
				diskEvent.AddEventData(StringData("Filesystem", it->filesystem));
				diskEvent.AddEventData(FloatData("PctFree", free));
				diskEvent.AddEventData(StringData("Severity", "WARN"));
				ret.push_back(diskEvent);
			}
			else
			{
				SensorEvent diskEvent(name);
				diskEvent.AddEventData(StringData("Filesystem", it->filesystem));
				diskEvent.AddEventData(FloatData("PctFree", free));
				diskEvent.AddEventData(StringData("Severity", "INFO"));
				ret.push_back(diskEvent);
			}
		}
	}
	return ret;
}