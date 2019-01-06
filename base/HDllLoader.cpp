#include "HDllLoader.h"
#include <iostream>
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
HDllLoader::HDllLoader(std::string filename) : dll_name(filename)
{
}

bool HDllLoader::load()
{
	if (dll)
		FreeLibrary(dll);
	dll = LoadLibrary(s2ws(dll_name).c_str());

	if (!dll) {
		std::cout << "[" << GetLastError() << "]";

		return false;
	}
	else {
		HPackageHandle t = (HPackageHandle)GetProcAddress(dll, "HLang_Package");
		if (!t) {
			return false;
		}
		else {
			classes = t();
		}
	}
	return true;
}

bool HDllLoader::load(std::string filename)
{
	this->dll_name = filename;
	return this->load();
}

HLANG_DLLEXPORT_MAP HDllLoader::get()
{
	return *classes;
}

HDllLoader::~HDllLoader()
{
	FreeLibrary(dll);
}