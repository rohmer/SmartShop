#include "TPLinkAPI.h"


std::string TPLinkAPI::encrypt(std::string input)
{
	uint8_t xorKey = 171;
	uint32_t sz = input.length();
	int32bit.integer = sz;
	uint32_t outputLength = sz + sizeof(int32bit.integer);
	uint8_t output[outputLength];
	int headerSize = sizeof(int32bit.integer);
	for (int i = 0; i < headerSize; i++) {
		output[i] = int32bit.byte[headerSize - 1 - i];
	}
	for (int i = 0; i < sz; i++)
	{
		output[i + headerSize] = input[i] ^ xorKey;
		xorKey = output[i + headerSize];
	}
	std::stringstream ss;
	for (int i = 0; i < outputLength; i++)
		ss << output[i];
	return ss.str();
}

std::string TPLinkAPI::decrypt(std::string input)
{
	uint32_t sz = input.length();
	std::stringstream ss;
	uint8_t xorKey = 171;
	for (int i = 0; i < sz; i++)
	{
		ss << (input[i] ^ xorKey);
		xorKey = input[i];
	}
	return ss.str();
}

std::vector<sTPLinkIOTDevice> TPLinkAPI::Discovery(uint timeout)
{
	std::vector<sTPLinkIOTDevice> devices;
	
	struct sockaddr_in si_me, si_other;

	int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	int broadcast = 1;
	int reuse_port = 1;
	int reuse_address = 1;

	setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse_address, sizeof(reuse_address));
	memset(&si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(9999);
	si_me.sin_addr.s_addr = INADDR_ANY;
	::bind(s, (sockaddr *)&si_me, sizeof(sockaddr));
	bool processing = true;

	uint ctr = 0;
	while (processing) {

		char buf[1024];
		unsigned slen = sizeof(sockaddr);

		int n = recvfrom(s, buf, sizeof(buf) - 1, 0, (sockaddr *)&si_other, &slen);
		
		std::string response = decrypt(buf);
		
		try
		{
			cJSON *json = cJSON_Parse(response.c_str());
			TPLinkDevice device = TPLinkDevice(json);
			devices.push_back(sTPLinkIOTDevice(inet_ntoa((struct in_addr)si_other.sin_addr),eTPLinkDeviceType::SmartPlug));

		}
		catch (const std::exception&)
		{
			
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ctr++;
		if (ctr > timeout)
			processing = false;
	}

}