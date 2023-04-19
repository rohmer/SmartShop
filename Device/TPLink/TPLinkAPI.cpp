#include "TPLinkAPI.h"


uint8_t *TPLinkAPI::encrypt(std::string input)
{
	uint8_t key = 0xab;
	uint8_t *buffer = new uint8_t[input.length()];
	for (int i = 0; i < input.length(); i++)
	{
		buffer[i] ^= key;
		key = buffer[i];
	}
	
	return buffer;
}

uint8_t *TPLinkAPI::encryptWithHeader(std::string input)
{
	uint8_t key = 0xab;
	uint8_t *buffer = new uint8_t[input.length() + 4];
	union u_int32
	{
		std::uint32_t inputVal;
		std::uint8_t outputBytes[4];
	};
	u_int32 header;
	header.inputVal = input.length();
	for (int i = 0; i < 3; i++)
	{
		buffer[i] = header.outputBytes[i];
	}
	uint8_t *enc = encrypt(input);
	for (int i = 0; i < input.length(); i++)
	{
		buffer[i + 4] = enc[i];
	}
	return buffer;
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
	
#define BROADCAST_PORT 9999u
	struct sockaddr_in s;

	int sockFD = socket(AF_INET, SOCK_DGRAM, 0);
    
	if (sockFD < 0)
		return devices;
	int trueflag = 1;
	if (setsockopt(sockFD,
		SOL_SOCKET,
		SO_BROADCAST,
		&trueflag,
		sizeof trueflag) < 0)
	{
		Logger::GetInstance()->LogC("Set options");
	}
	if (setsockopt(sockFD,
		SOL_SOCKET,
		SO_REUSEADDR,
		&trueflag,
		sizeof trueflag) < 0)
	{
		Logger::GetInstance()->LogC("Set options");
	}
	
		
	memset(&s, '\0', sizeof(struct sockaddr_in));
	s.sin_family = AF_INET;
	s.sin_port = htons(BROADCAST_PORT);
	s.sin_addr.s_addr = INADDR_BROADCAST; 

	uint8_t *val=encryptWithHeader("get_sysinfo");
	if (sendto(sockFD, val, sizeof(val), 15, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
		perror("sendto");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	char buffer[1024];
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	std::stringstream sstr;
	while (true)
	{				
		bzero(buffer, sizeof(buffer));
		int rval = recvfrom(sockFD,
			(char *)buffer,
			1024, 
			MSG_DONTWAIT,
			(struct sockaddr *) &cliaddr,
			&len);
		if (rval < 0)
		{
			break;
		}
		if (rval == 0)
		{
			break;
		}
		sstr << std::string( reinterpret_cast<char const*>(buffer), rval );
	}
	std::string decrypted = decrypt(sstr.str());
}