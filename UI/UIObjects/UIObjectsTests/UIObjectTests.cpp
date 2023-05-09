#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char *argv[])
{

	MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
	CommandLineTestRunner::RunAllTests(argc, argv);
	return 0;
}