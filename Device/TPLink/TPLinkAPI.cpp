#include "TPLinkAPI.h"


uint8_t *TPLinkAPI::encode(size_t *outputLength, const char *message)
{
	size_t srcmsg_len;
	uint8_t *d;
	uint32_t temp;

	if (message == NULL)
		return NULL;

	srcmsg_len = strlen(message);
	*outputLength = srcmsg_len + 4;
	d = (uint8_t *)calloc(1, *outputLength);
	if (d == NULL)
		return NULL;
	if (!encrypt(d + 4, (uint8_t *) message, srcmsg_len)) {
		free(d);
		return NULL;
	}
	temp = htonl(srcmsg_len);
	memcpy(d, &temp, 4);

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

	if (!decrypt((uint8_t *) outbuf, s + 4, in_s_len)) {
		free(outbuf);
		return NULL;
	}

	return outbuf;
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
	
		
	memset(&s, '\0', sizeof(struct sockaddr_in));
	s.sin_family = AF_INET;
	s.sin_port = htons(BROADCAST_PORT);
	s.sin_addr.s_addr = INADDR_BROADCAST; 
	size_t sz;
		
	if (sendto(sockFD, "", 0, sz, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
		perror("sendto");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	size_t msglen;
	size_t recvsize = recv(sockFD, &msglen, sizeof(msglen), MSG_PEEK);
	if (recvsize != sizeof(msglen)) {
		return devices;
	}
	msglen = ntohl(msglen) + 4;
	uint8_t *recvbuf;
	recvbuf = (uint8_t *)calloc(1, (size_t) msglen);
	recvsize = recv(sockFD, recvbuf, msglen, MSG_WAITALL);
	close(sockFD);
	uint8_t *msg = decode(recvbuf, msglen);
	free(recvbuf);
	
}