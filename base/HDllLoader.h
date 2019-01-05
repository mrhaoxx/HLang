#pragma once
#include "HObject.h"
#include <string>
#include <Windows.h>
class HDllLoader
{
public:
	HDllLoader(std::string filename);
	bool load();
	bool load(std::string filename);
	std::map<std::string, HFunctionAddress> get();
	~HDllLoader();
private:
	std::string dll_name;
	typedef std::map < std::string, HFunctionAddress>(*HPackageHandle)();
	std::map < std::string, HFunctionAddress> classes;
	HINSTANCE dll;
};
