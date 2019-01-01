#include <iostream>
#include "HExecutor.h"
int main()
{
	HLang::HExecutor test;
	test._new_("i", "int", HArgs());
	test._run_("i", "", HArgs);
}