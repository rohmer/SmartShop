#pragma once

#include <string>

struct dbstat {
	std::string name;
	std::string path;
	int pageno = 0;
	std::string pagetype;
	int ncell = 0;
	int payload = 0;
	int unused = 0;
	int mx_payload = 0;
	int pgoffset = 0;
	int pgsize = 0;
};