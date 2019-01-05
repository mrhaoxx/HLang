#include <iostream>
#include "HDomain.h"
#include "HInt.h"
#include "HByte.h"
int main()
{
	//Next Step String
	HLang::HDomain dm;
	dm.LoadDll("std");
	dm.New("test", "string", HArgs());
	dm.Execute("test", "insert", HArgs({ HLang::HByte::__new__(HArgs())->to <HLang::HByte>()->setvalue('t') }));
	dm;
}