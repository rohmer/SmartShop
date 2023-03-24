#pragma once

#include "crc32.h"
#include "md5.h"
#include "sha1.h"
#include "sha3.h"
#include "sha256.h"

class HashLib
{	
public:
	enum eHashMethod
	{
		eCRC32,
		eMD5,
		eSHA1,
		eSHA3,
		eSHA256
	};

	static std::string ComputeHash(std::string inputString, eHashMethod hashMethod = eMD5);
};