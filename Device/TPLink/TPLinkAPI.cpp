#include "TPLinkAPI.h"


uint8_t *TPLinkAPI::encode(size_t *outputLength, const char *message, bool addHeader)
{
	size_t srcmsg_len;
	uint8_t *d;
	uint32_t temp;

	if (message == NULL)
		return NULL;

	srcmsg_len = strlen(message);
	if (addHeader)
		*outputLength = srcmsg_len + 4;
	else
		*outputLength = srcmsg_len;

	d = (uint8_t *)calloc(1, *outputLength);
	if (d == NULL)
		return NULL;
	if (addHeader)
	{
		if (!encrypt(d + 4, (uint8_t *) message, srcmsg_len))
		{
			free(d);
			return NULL;
		}
	}
	else
	{
		if (!encrypt(d, (uint8_t *)message, srcmsg_len))
		{
			free(d);
			return NULL;
		}
		
	}
	if (addHeader)
	{
		temp = htonl(srcmsg_len);
		memcpy(d, &temp, 4);
	}
	return d;
}

bool TPLinkAPI::encrypt(uint8_t *d, const uint8_t *s, size_t len)
{
	uint8_t key, temp;
	size_t i;

	if (d == NULL)
		return false;
	if (s == NULL)
		return false;
	if (len == 0)
		return false;

	key = 0xab;
	for (i = 0; i < len; i++) {
		temp = key ^ s[i];
		key = temp;
		d[i] = temp;
	}
	return true;
}

bool TPLinkAPI::decrypt(uint8_t *d, const uint8_t *s, size_t len)
{
	uint8_t key, temp;
	size_t i;

	if (d == NULL)
		return false;
	if (s == NULL)
		return false;
	if (len == 0)
		return false;

	key = 0xab;
	for (i = 0; i < len; i++) {
		temp = key ^ s[i];
		key = s[i];
		d[i] = temp;
	}
	return true;
}

uint8_t *TPLinkAPI::decode(const uint8_t *s, size_t s_len)
{
	uint32_t in_s_len;
	uint8_t *outbuf;

	if (s == NULL)
		return NULL;
	if (s_len <= 4)
		return NULL;

	memcpy(&in_s_len, s, 4);
	in_s_len = ntohl(in_s_len);
	if ((s_len - 4) < in_s_len) {
		/* packet was cut short- adjust in_s_len */
		in_s_len = s_len - 4;
	}

	outbuf = (uint8_t *)calloc(1, in_s_len + 1);

	if (!decrypt((uint8_t *) outbuf, s, in_s_len)) {
		free(outbuf);
		return NULL;
	}

	return outbuf;
}

std::vector<std::shared_ptr<TPLink_Device>> TPLinkAPI::Discovery(uint timeout)
{
	std::vector<std::shared_ptr<TPLink_Device>> devices;
	
#define SERVERPORT 9999
	struct sockaddr_in send_addr, recv_addr;
	int trueflag = 1, count = 0;
	int fd;
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		perror("socket");
	if (setsockopt(fd,
		SOL_SOCKET,
		SO_BROADCAST,
		&trueflag,
		sizeof trueflag) < 0)
		perror("setsockopt");

	memset(&send_addr, 0, sizeof send_addr);
	send_addr.sin_family = AF_INET;
	send_addr.sin_port = (in_port_t) htons(SERVERPORT);
	// broadcasting address for unix (?)
	inet_aton("255.255.255.255", &send_addr.sin_addr);
	if (setsockopt(fd,
		SOL_SOCKET,
		SO_REUSEADDR,
		&trueflag,
		sizeof trueflag) < 0)
		perror("setsockopt");

	memset(&recv_addr, 0, sizeof recv_addr);
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = (in_port_t) htons(SERVERPORT);
	recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd, (struct sockaddr*) &recv_addr, sizeof recv_addr) < 0)
		perror("bind");
	std::string cmd = "{\"system\":{\"get_sysinfo\":{}}}";

	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.c_str(), false);
	if (sendto(fd,
		d,
		length,
		0,
		(struct sockaddr*) &send_addr,
		sizeof send_addr) < 0)
		perror("send");

	free(d);
	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) < 0)
		perror("NonBlock");
	
	uint8_t ctr = 0;
	bool isFirst = true;
	while (ctr<timeout) {
		char sbuf[8192];
		sockaddr_in from;
		socklen_t socksz = sizeof(from);
		int rsize = recvfrom(fd, sbuf, sizeof(sbuf) - 1, 0, (struct sockaddr*)&from, &socksz);
		if (rsize <= 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			ctr++;
		}
		else
		{
			char tmpc[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &from.sin_addr, tmpc, INET_ADDRSTRLEN);
			char *p = &sbuf[0];
			uint8_t *outbuf = (uint8_t *)calloc(1, rsize + 1);
			bool ret = decrypt(outbuf, (uint8_t*)p, rsize);
			if (!isFirst)
			{
				std::string msg((char *)outbuf); 
				std::string inet(tmpc);
				std::shared_ptr<TPLink_Device> dev = parseResponse(msg, inet);
				if (dev!=NULL)
					devices.push_back(dev);
			}
			if (isFirst)
				isFirst = false;
		}		
	}
	close(fd);
	
	return devices;
}

std::shared_ptr<TPLink_Device> TPLinkAPI::parseResponse(std::string response, std::string ipAddr)
{
	cJSON *json = cJSON_Parse(response.c_str());
	if (json == NULL)
		return NULL;
	std::shared_ptr<TPLink_Device> dev = DeviceFactory::CreateDevice(json, ipAddr);
	return dev;
}

bool TPLinkAPI::SetAlias(TPLink_Device host, std::string alias)
{
	return SetAlias(host.GetIPAddress(), alias);
}

std::string TPLinkAPI::sendCommand(uint8_t *cmd, size_t cmdLen, std::string host)
{
	int fd;
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		perror("socket");
	struct sockaddr_in send_addr;
	memset(&send_addr, 0, sizeof send_addr);
	send_addr.sin_family = AF_INET;
	send_addr.sin_port = (in_port_t) htons(SERVERPORT);
	inet_pton(AF_INET, host.c_str(), &(send_addr.sin_addr));
	if (sendto(fd,
		cmd,
		cmdLen,
		0,
		(struct sockaddr*) &send_addr,
		sizeof send_addr) < 0)
	{
		free(cmd);
		return "";
	}
	free(cmd);
	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) < 0)
		perror("NonBlock");
	char sbuf[8192];
	sockaddr_in from;
	socklen_t socksz = sizeof(from);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	int rsize = recvfrom(fd, sbuf, sizeof(sbuf) - 1, 0, (struct sockaddr*)&from, &socksz);
	if (rsize <= 0)
	{
		close(fd);
		return "";
	}
	char *p = &sbuf[0];
	uint8_t *outbuf = (uint8_t *)calloc(1, rsize + 1);
	bool dec = decrypt(outbuf, (uint8_t*)p, rsize);
	std::string ret((char *)outbuf);
	close(fd);
	return ret;
}

bool TPLinkAPI::SetAlias(std::string host, std::string alias)
{
	std::stringstream cmd;
	cmd << "{\"system\":{\"set_dev_alias\":{\"alias\":\"" << alias << "\"}}}";
	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, host);
	
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "system"))
	{
		json = cJSON_GetObjectItem(json, "system");
		if (cJSON_HasObjectItem(json, "set_dev_alias"))
		{
			json = cJSON_GetObjectItem(json, "set_dev_alias");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int ec = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (ec == 0)
					return true;
			}
		}
	}
	return false;
}

bool TPLinkAPI::SetBrightness(TPLink_Device host, int brightness)
{
	if (host.GetDeviceType() == TPLink_Device::SmartBulb || 
		host.GetDeviceType() == TPLink_Device::SmartSwitchDimmer ||
		host.GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		SetBrightness(host.GetIPAddress(), brightness);
	}
	else
	{
		return false;
	}
}
bool TPLinkAPI::SetBrightness(std::string host, int brightness)
{
	std::stringstream cmd;
	cmd << "{\"smartlife.iot.smartbulb.lightingservice\":{\"transition_light_state\":{\"on_off\":1,\"dft_on_state\":{\"mode\":\"normal\",\"hue\":0,\"saturation\":0,\"color_temp\":2700,\"brightness\":"<<brightness<<"}";
	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, host);
	
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "smartlife.iot.smartbulb.lightingservice"))
	{
		json = cJSON_GetObjectItem(json, "smartlife.iot.smartbulb.lightingservice");
		if (cJSON_HasObjectItem(json, "transition_light_state"))
		{
			json = cJSON_GetObjectItem(json, "transition_light_state");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int ec = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (ec == 0)
					return true;
			}
		}
	}
	return false;
}

bool TPLinkAPI::RefreshItem(std::shared_ptr<TPLink_Device> &device)
{
	std::stringstream cmd;
	cmd << "{\"system\": {\"get_sysinfo\": null}}";
	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, device->GetIPAddress());
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "system"))
	{
		json = cJSON_GetObjectItem(json, "system");
		if (cJSON_HasObjectItem(json, "get_sysinfo"))
		{
			json = cJSON_GetObjectItem(json, "get_sysinfo");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int errcode = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (errcode != 0)
					return false;
			}
		}
	}
	device = parseResponse(response, device->GetIPAddress());
	return true;
}

bool TPLinkAPI::TurnOn(std::shared_ptr<TPLink_Device> host)
{
	return TurnOn(host->GetIPAddress());
}

bool TPLinkAPI::TurnOn(std::string ipAddr)
{
	std::stringstream cmd;
	cmd << "{\"system\":{\"set_relay_state\": {\"state\":1}}}";
	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, ipAddr);
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "system"))
	{
		json = cJSON_GetObjectItem(json, "system");
		if (cJSON_HasObjectItem(json, "get_sysinfo"))
		{
			json = cJSON_GetObjectItem(json, "set_relay_state");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int errcode = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (errcode != 0)
					return false;
			}
		}
	}
	return true;
}
	
bool TPLinkAPI::TurnOff(std::shared_ptr<TPLink_Device> host)
{
	return TurnOff(host->GetIPAddress());
}

bool TPLinkAPI::TurnOff(std::string ipAddr)
{
	std::stringstream cmd;
	cmd << "{\"system\":{\"set_relay_state\": {\"state\":0}}}";
	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, ipAddr);
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "system"))
	{
		json = cJSON_GetObjectItem(json, "system");
		if (cJSON_HasObjectItem(json, "get_sysinfo"))
		{
			json = cJSON_GetObjectItem(json, "set_relay_state");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int errcode = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (errcode != 0)
					return false;
			}
		}
	}
	return true;
}

bool TPLinkAPI::IsColor(std::shared_ptr<TPLink_Device> host)
{
	if (host->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> bulb = std::static_pointer_cast<TPLink_Bulb>(host);
		return bulb->IsColor();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(host);
		return bulb->IsColor();
	}
	return false;	
}

bool TPLinkAPI::IsDimmable(std::shared_ptr<TPLink_Device> host)
{
	if (host->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> bulb = std::static_pointer_cast<TPLink_Bulb>(host);
		return bulb->IsDimmable();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(host);
		return bulb->IsDimmable();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartSwitchDimmer)
	{
		std::shared_ptr<TPLink_DimmerSwitch> bulb = std::static_pointer_cast<TPLink_DimmerSwitch>(host);
		return bulb->IsDimmable();
	}
	return false;	
}

bool TPLinkAPI::IsVariableColorTemp(std::shared_ptr<TPLink_Device> dev)
{
	if (dev->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> device = std::static_pointer_cast<TPLink_Bulb>(dev);
		return device->IsVariableColorTemp();
	}
	if (dev->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(dev);
		return bulb->IsVariableColorTemp();
	}
	return false;
}

bool TPLinkAPI::IsOn(std::shared_ptr<TPLink_Device> host)
{
	RefreshItem(host);
	if (host->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> bulb = std::static_pointer_cast<TPLink_Bulb>(host);
		return bulb->IsOn();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(host);
		return bulb->IsOn();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartSwitch)
	{
		std::shared_ptr<TPLink_Switch> bulb = std::static_pointer_cast<TPLink_Switch>(host);
		return bulb->IsOn();
	}
	if (host->GetDeviceType() == TPLink_Device::SmartSwitchDimmer)
	{
		std::shared_ptr<TPLink_DimmerSwitch> bulb = std::static_pointer_cast<TPLink_DimmerSwitch>(host);
		return bulb->IsOn();
	}
}

bool TPLinkAPI::GetColorTemp(std::shared_ptr<TPLink_Device> host, int &colorTemp)
{
	if (IsVariableColorTemp(host))
		return false;
	if (!RefreshItem(host))
		return false;
	if (host->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> bulb = std::static_pointer_cast<TPLink_Bulb>(host);
		colorTemp = bulb->GetColorTemp();
		return true;
	}
	if (host->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(host);
		colorTemp = bulb->GetColorTemp();
		return true;
	}
}
bool TPLinkAPI::GetHSV(std::shared_ptr<TPLink_Device> host, int &h, int &s, int &v)
{
	if (!IsColor(host))
		return false;
	if (!RefreshItem(host))
		return false;
	if (host->GetDeviceType() == TPLink_Device::SmartBulb)
	{
		std::shared_ptr<TPLink_Bulb> bulb = std::static_pointer_cast<TPLink_Bulb>(host);
		h = bulb->GetHue();
		s = bulb->GetSaturation();
		v = bulb->GetBrightness();
		return true;
	}
	if (host->GetDeviceType() == TPLink_Device::SmartLightStrip)
	{
		std::shared_ptr<TPLink_LightStrip> bulb = std::static_pointer_cast<TPLink_LightStrip>(host);
		h = bulb->GetHue();
		s = bulb->GetSaturation();
		v = bulb->GetBrightness();
		return true;
	}
	return false;
}
bool TPLinkAPI::SetHSV(std::shared_ptr<TPLink_Device> host,
	int hue, 
	int saturation, 
	int brightness)
{
	if (!IsColor(host))
		return false;
	std::stringstream cmd;
	int colorTemp;
	GetColorTemp(host, colorTemp);
	int of = 0;
	if (IsOn(host))
		of = 1;
	cmd << "{\"smartlife.iot.smartbulb.lightingservice\": {\"transition_light_state\": {\"hue\": " << hue << ", \"saturation\": " << saturation << ", \"color_temp\": " << colorTemp << ", \"brightness\": " << brightness << ", ";
	cmd << "\"on_off\": " << of << ", \"ignore_default\": 1}}}";

	size_t length;
	uint8_t *d;
	d = encode(&length, cmd.str().c_str(), false);
	std::string response = sendCommand(d, length, host->GetIPAddress());
	cJSON *json = cJSON_Parse(response.c_str());
	if (cJSON_HasObjectItem(json, "smartlife.iot.smartbulb.lightingservice"))
	{
		json = cJSON_GetObjectItem(json, "smartlife.iot.smartbulb.lightingservice");
		if (cJSON_HasObjectItem(json, "transition_light_state"))
		{
			json = cJSON_GetObjectItem(json, "transition_light_state");
			if (cJSON_HasObjectItem(json, "err_code"))
			{
				int errcode = cJSON_GetObjectItem(json, "err_code")->valueint;
				if (errcode != 0)
					return false;
			}
		}
	}
	return true;
}