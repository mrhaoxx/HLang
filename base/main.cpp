#include <iostream>
#include "HDomain.h"
#include "HInt.h"
int main()
{
	HLang::HDomain dm;
	dm.LoadDll("std");
	dm.New("test", "t", HArgs());
	dm.Execute("test", "hello", HArgs());
}