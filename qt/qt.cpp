#include "qt.h"

#include <Windows.h>
#include "HQHelloWorld.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
HLANG_DLLPACKAGES{
	return new HLANG_DLLEXPORT_MAP({std::make_pair("qt",&HLang::HQHelloWorld::__new__)});
}