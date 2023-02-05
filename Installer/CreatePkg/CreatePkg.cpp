#include <iostream>
#include <fstream>

#include <cjson/cJSON.h>

#include "Options.h"
#include "PackageDescriptor.h"

using namespace std;
std::string Options::Name, Options::InstallDir, Options::Desc, Options::SoftwareName;
Version Options::Ver;

int main(int argc, char *argv[])
{
	if (!Options::ParseOpts(argc, argv))
		return -1;
	
	PackageDescriptor pd(Options::Name, Options::Desc, Options::SoftwareName, Options::InstallDir, Options::Ver);
	
	cJSON *pjson = pd.ToJSON();
	
	try
	{
		std::ofstream file;
		file.open("package.json", _S_out);
	
		file << cJSON_Print(pjson);
		file.close();		
	}
	catch (const std::exception&)
	{
		std::cout << "Error writing file\n\n";
		return -1;
	}
	
	return 0;
}