#include "TPLinkDevice.h"

TPLinkDevice::TPLinkDevice(cJSON *discovery)
{
	if (cJSON_HasObjectItem(discovery, "sw_ver"))
		swVersion = cJSON_GetObjectItem(discovery, "sw_ver")->valuestring;
	if (cJSON_HasObjectItem(discovery, "hw_ver"))
		HWVersion = cJSON_GetObjectItem(discovery, "hw_ver")->valuedouble;
	if (cJSON_HasObjectItem(discovery, "type"))
		stringType = cJSON_GetObjectItem(discovery, "type")->valuestring;
	if (cJSON_HasObjectItem(discovery, "model"))
		model = cJSON_GetObjectItem(discovery, "model")->valuestring;
	if (cJSON_HasObjectItem(discovery, "dev_name"))
		deviceName= cJSON_GetObjectItem(discovery, "dev_name")->valuestring;
	if (cJSON_HasObjectItem(discovery, "relay_state"))
		relayState = (bool)cJSON_GetObjectItem(discovery, "relay_state")->valueint;
	if (cJSON_HasObjectItem(discovery, "on_time"))
		onTime= cJSON_GetObjectItem(discovery, "on_time")->valueint;
	if (cJSON_HasObjectItem(discovery, "active_mode"))
		activeMode = cJSON_GetObjectItem(discovery, "active_mode")->valuestring;
	if (cJSON_HasObjectItem(discovery, "feature"))
		feature = cJSON_GetObjectItem(discovery, "feature")->valuestring;
	if (cJSON_HasObjectItem(discovery, "updating"))
		updating = (bool)cJSON_GetObjectItem(discovery, "updating")->valueint;
	if (cJSON_HasObjectItem(discovery, "rssi"))
		rssi = cJSON_GetObjectItem(discovery, "rssi")->valueint;
	if (cJSON_HasObjectItem(discovery, "led_off"))
		ledOff = (bool)cJSON_GetObjectItem(discovery, "led_off")->valueint;
	if (cJSON_HasObjectItem(discovery, "alias"))
		alias = cJSON_GetObjectItem(discovery, "alias")->valuestring;
	if (cJSON_HasObjectItem(discovery, "deviceID"))
		deviceID = cJSON_GetObjectItem(discovery, "deviceId")->valuestring;
	if (cJSON_HasObjectItem(discovery, "hwId"))
		hwID = cJSON_GetObjectItem(discovery, "hwId")->valuestring;
	if (cJSON_HasObjectItem(discovery, "oemId"))
		oemID = cJSON_GetObjectItem(discovery, "oemId")->valuestring;
	if (cJSON_HasObjectItem(discovery, "latitude"))
		lattitude = cJSON_GetObjectItem(discovery, "latitude")->valuedouble;
	if (cJSON_HasObjectItem(discovery, "longitude"))
		longitude = cJSON_GetObjectItem(discovery, "longitude")->valuedouble;
	if (cJSON_HasObjectItem(discovery, "mac"))
		macAddr = cJSON_GetObjectItem(discovery, "mac")->valuestring;
	if (cJSON_HasObjectItem(discovery, "err_code"))
		errorCode = cJSON_GetObjectItem(discovery, "err_code")->valueint;
	
	
}