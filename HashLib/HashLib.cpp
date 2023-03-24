#include "HashLib.h"

std::string HashLib::ComputeHash(std::string input, eHashMethod hashAlgo)
{
	switch (hashAlgo)
	{
	case eCRC32:
		{
			CRC32 hasher;
			return hasher(input);
		}
	case eMD5:
		{
			MD5 hasher;
			return hasher(input);
		}
	case eSHA1:
		{
			SHA1 hasher;
			return hasher(input);
		}
	case eSHA3:
		{
			SHA3 hasher;
			return hasher(input);
		}		
	case eSHA256:
		{
			SHA256 hasher;
			return hasher(input);
		}		
	}
	return "";
}