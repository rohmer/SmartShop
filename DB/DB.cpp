#include "DB.h"

DB *DB::instance = NULL;

DB::DB(std::string path) :
	path(path)
{
}

DB *DB::GetInstance(std::string path)
{
	if (instance == NULL)
	{
		instance = new DB(path);
		instance->init();
	}
	
	return instance;
}

void DB::init()
{
	using Storage = decltype(initCoreStorage(""));
	storage = std::make_shared<Storage>(initCoreStorage(path));
	try
	{
		storage->sync_schema();
	}
	catch (std::system_error &e)
	{
		std::cerr << "Exception Syncing Schema: " << e.what() << "\n\n\n";
		return;
	}
	initialized = true;
}
