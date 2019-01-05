#pragma once
#include <HObject.h>
HLANG_NAMESPACE_START
class HHelloWorld :
	public HObject
{
	HLANG_OBJECT(HHelloWorld);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HHelloWorld, hello, HLANG_ARGSPILT(""), &HHelloWorld::say);
	HLANG_INIT_END
public:
	HPointer say(HArgs args);
};

HLANG_NAMESPACE_END