// std.cpp : 定义 DLL 应用程序的导出函数。
//

#include "HObject.h"
#include "HString.h"
#include "HHelloWorld.h"
HLANG_DLLPACKAGES
{
	return new std::map<std::string,HFunctionAddress>({std::make_pair("t",&HLang::HHelloWorld::__new__)});
}