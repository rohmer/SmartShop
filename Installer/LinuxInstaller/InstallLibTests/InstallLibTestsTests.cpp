#include <filesystem>
#include <string>
#include "../InstallLib/InstallLib.h"
#include "../InstallLib/DecompUtil.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

/*
	This is a very basic sample demonstrating the CppUTest framework.
	Read more about CppUTest syntax here: https://cpputest.github.io/manual.html
*/

std::string randomStrGen(int length) {
	static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::string result;
	result.resize(length);

	for (int i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];

	return result;
}

TEST_GROUP(Decompression)
{
	void setup()
	{
		srand(time(NULL));
	}
};

TEST(Decompression, DecompressPackage)
{
	std::stringstream p;
	p << std::filesystem::temp_directory_path().string() << std::filesystem::path::preferred_separator << randomStrGen(8);

	std::filesystem::create_directory(p.str());
	
	bool res=DecompUtil::DecompressZip("/tmp/ZeroConf.pkg", p.str());

	std::filesystem::remove_all(p.str());
	CHECK(res);
}
