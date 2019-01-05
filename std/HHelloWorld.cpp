#include "HHelloWorld.h"
#include <iostream>
#include "HVoid.h"

HPointer HLang::HHelloWorld::say(HArgs args)
{
	std::cout << "Hello World";
	return new HVoid;
}