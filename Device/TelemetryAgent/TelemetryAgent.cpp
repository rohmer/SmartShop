#include "TelemetryAgent.h"

TelemetryAgent::TelemetryAgent(DeviceConfig dc) :
	DeviceBase("Telemetry Agent", 
		"Agent for getting metrics about the underlying device", 
		eDeviceType::SENSOR, 
		eDeviceBus::NA, 300)
{
	enabled = true;
	UpdateConfig(dc);
}

void TelemetryAgent::UpdateConfig(DeviceConfig dc)
{
	if (dc.HasConfigItem("Enabled"))
		enabled = dc.GetConfigItem("Enabled").GetBoolVal();
	if (dc.HasConfigItem("TempWarn"))
		tempWarn = dc.GetConfigItem("TempWarn").GetFloatVal();
	if (dc.HasConfigItem("PollingInterval"))
		SetPollingInterval(dc.GetConfigItem("PollingInterval").GetLongVal());
	if (dc.HasConfigItem("TempCrit"))
		tempCrit = dc.GetConfigItem("TempCrit").GetFloatVal();
	if (dc.HasConfigItem("DiskPctWarn"))
		diskWarn = dc.GetConfigItem("DiskPctWarn").GetFloatVal();
	if (dc.HasConfigItem("DiskPctCrit"))
		diskCrit = dc.GetConfigItem("DiskPctCrit").GetFloatVal();
	if (dc.HasConfigItem("RootFSOnly"))
		onlyRootFS = dc.GetConfigItem("RootFSOnly").GetBoolVal();
}

TelemetryAgent::TelemetryAgent(
	std::string Name,
	std::string Description,
	unsigned int PollingInterval,
	float TempWarning,
	float TempCrit,
	float DiskPctWarn,
	float DiskPctCrit,
	bool OnlyReportRootFS)
	: DeviceBase(Name, Description, eDeviceType::SENSOR, eDeviceBus::NA, PollingInterval)
	, tempWarn(TempWarning)
	, tempCrit(TempCrit)
	, diskWarn(DiskPctWarn)
	, diskCrit(DiskPctCrit)
	, onlyRootFS(OnlyReportRootFS)
{
	config.AddConfigItem(DeviceConfigItem("TempWarn", TempWarning));
	config.AddConfigItem(DeviceConfigItem("TempCrit", TempCrit));
	config.AddConfigItem(DeviceConfigItem("DiskPctWarn", DiskPctWarn));
	config.AddConfigItem(DeviceConfigItem("DiskPctCrit", DiskPctCrit));
	config.AddConfigItem(DeviceConfigItem("RootFSOnly", OnlyReportRootFS));
	if (tempWarn > tempCrit)
		tempWarn = tempCrit;
	if (diskWarn > diskCrit)
		diskWarn = diskCrit;
}

std::vector<SensorEvent> TelemetryAgent::PollSensor()
{
	if (!enabled)
		return std::vector<SensorEvent>();
	
	tempCrit = config.GetConfigItem("TempCrit").GetFloatVal();
	tempWarn = config.GetConfigItem("TempWarn").GetFloatVal();
	diskCrit = config.GetConfigItem("DiskPctCrit").GetFloatVal();
	diskWarn = config.GetConfigItem("DiskPctWarn").GetFloatVal();
	onlyRootFS = config.GetConfigItem("RootFSOnly").GetBoolVal();
	
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
		if (!onlyRootFS || std::strcmp(it->filesystem.c_str(), "/"))
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
	}
	return ret;
}

// the class factories
extern "C" DeviceBase* create() 
{
	TelemetryAgent *obj = new TelemetryAgent();
	return ((DeviceBase *)obj);
}

extern "C" void destroy(TelemetryAgent *p) 
{
	delete p;
}