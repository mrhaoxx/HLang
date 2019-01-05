#include <iostream>
#include "HDomain.h"
#include "HInt.h"
int main()
{
	HLang::HDomain dm;
	dm.RegisterClass("base", "int", &HLang::HInt::__new__);
	dm.New("i", "int", HArgs());
	dm.Access("i")->__do__("hw", HArgs({ HLang::HInt::__new__(HArgs())->to<HLang::HInt>()->setvalue(200) }));
	//Test
}