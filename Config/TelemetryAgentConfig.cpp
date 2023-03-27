#include "TelemetryAgentConfig.h"

TelemetryAgentConfig::TelemetryAgentConfig(
	uint PollingInterval, 
	float TempWarn,
	float TempCrit,
	float DiskWarn,
	float DiskCrit,
	bool OnlyReportRootFS)
	: pollingInt(PollingInterval)
	, tempWarn(TempWarn)
	, tempCrit(TempCrit)
	, diskWarn(DiskWarn)
	, diskCrit(DiskCrit)
	, onlyRootFS(OnlyReportRootFS)
{
}

TelemetryAgentConfig TelemetryAgentConfig::FromJSON(cJSON *json)
{
	uint poll = 300;
	float tWarn = 50.0, tCrit = 60.0, dWarn = 50.0, dCrit = 20.0;
	bool rootFS = true;
	if (cJSON_HasObjectItem(json, "pollingInt"))
		poll = cJSON_GetObjectItem(json, "pollingInt")->valueint;
	if (cJSON_HasObjectItem(json, "tempWarn"))
		tWarn = cJSON_GetObjectItem(json, "tempWarn")->valuedouble;
	if (cJSON_HasObjectItem(json, "tempCrit"))
		tCrit = cJSON_GetObjectItem(json, "tempCrit")->valuedouble;
	if (cJSON_HasObjectItem(json, "diskWarn"))
		dWarn = cJSON_GetObjectItem(json, "diskWarn")->valuedouble;
	if (cJSON_HasObjectItem(json, "diskCrit"))
		dCrit = cJSON_GetObjectItem(json, "diskCrit")->valuedouble;
	if (cJSON_HasObjectItem(json, "onlyRootFS"))
		rootFS = (bool)cJSON_GetObjectItem(json, "onlyRootFS")->valueint;
	return TelemetryAgentConfig(poll, tWarn, tCrit, dWarn, dCrit, rootFS);
}

cJSON *TelemetryAgentConfig::ToJSON()
{
	cJSON *json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "pollingInt", cJSON_CreateNumber(pollingInt));
	cJSON_AddItemToObject(json, "tempWarn", cJSON_CreateNumber(tempWarn));
	cJSON_AddItemToObject(json, "tempCrit", cJSON_CreateNumber(tempCrit));
	cJSON_AddItemToObject(json, "diskWarn", cJSON_CreateNumber(diskWarn));
	cJSON_AddItemToObject(json, "diskCrit", cJSON_CreateNumber(diskCrit));
	cJSON_AddItemToObject(json, "onlyRootFS", cJSON_CreateNumber(onlyRootFS));
	return json;
}

std::vector<DeviceConfigItem> TelemetryAgentConfig::ToDeviceConfig()
{
	std::vector<DeviceConfigItem> ret;
	ret.push_back(DeviceConfigItem("pollingInt",(long)pollingInt));
	ret.push_back(DeviceConfigItem("tempWarn", tempWarn));
	ret.push_back(DeviceConfigItem("tempCrit", tempCrit));
	ret.push_back(DeviceConfigItem("diskWarn", diskWarn));
	ret.push_back(DeviceConfigItem("diskCrit", diskCrit));
	ret.push_back(DeviceConfigItem("onlyRootFS", onlyRootFS));
	return ret;
}

TelemetryAgentConfig TelemetryAgentConfig::FromDeviceConfig(DeviceConfig dc)
{
	uint poll = 300;
	float tWarn = 50.0, tCrit = 60.0, dWarn = 50.0, dCrit = 20.0;
	bool rootFS = true;
	if (dc.HasConfigItem("pollingInt"))
		poll = dc.GetConfigItem("pollingInt").GetLongVal();
	if (dc.HasConfigItem("tempWarn"))
		tWarn = dc.GetConfigItem("tempWarn").GetFloatVal();
	if (dc.HasConfigItem("tempCrit"))
		tCrit = dc.GetConfigItem("tempCrit").GetFloatVal();
	if (dc.HasConfigItem("diskCrit"))
		dWarn = dc.GetConfigItem("diskWarn").GetFloatVal();
	if (dc.HasConfigItem("diskCrit"))
		dCrit = dc.GetConfigItem("diskCrit").GetFloatVal();
	if (dc.HasConfigItem("onlyRootFS"))
		rootFS = dc.GetConfigItem("onlyRootFS").GetBoolVal();
	return TelemetryAgentConfig(poll, tWarn, tCrit, dWarn, dCrit, rootFS);
}

void TelemetryAgentConfig::Update()
{
	DeviceManager *dm = DeviceManager::GetInstance();
	TelemetryAgent *ta = dynamic_cast<TelemetryAgent*>(dm->GetDeviceByName("Telemetry Agent"));
	if (ta == NULL)
	{
		Logger::GetInstance()->LogW("Could not find a Telemetry Agent to update");
		return;
	}
	DeviceConfig dc = ta->GetConfig();
	std::vector<DeviceConfigItem> items = ToDeviceConfig();
	for (int i = 0; i < items.size(); i++)
		dc.SetConfigItem(items[i]);
	ta->UpdateConfig(dc);
	
}