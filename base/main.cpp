#include <iostream>
#include "HDomain.h"
#include "HInt.h"
#include "HByte.h"
#include "HString.h"
using namespace HLang;
int main()
{
	//Next Step String
	HLang::HDomain dm;
	dm.RegisterClass("base", "string", &HLang::HString::__new__);
	dm.New("t", "string", HArgs());
	dm.Access("t")->to<HLang::HVector>()->to<HLang::HString>()->setvalue("Hello World");
	std::cout << dm.Access("t")->to<HLang::HVector>()->to<HLang::HString>()->toStdString();
	dm.LoadDll("qt");
	dm.New("q", "qt", HArgs());
	dm.Execute("q", "aboutQt", HArgs());
	dm.Execute("q", "info", HArgs({ dm.Access("t") }));
	return 0;
}