#include "HBuiltin.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HBaseInterface.h"
H_MemberFunction_def(newclass, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	if (GetArg(0) == "HWindow")
		return (HObject*)new HWindow;
	else if (GetArg(0) == "HPushButton")
		return (HObject*)new HPushButton(nullptr);
	else if (GetArg(0) == "HFunction")
		return new HFunction;
	else if (GetArg(0) == "HBool")
		return new HBool(false);
	else if (GetArg(0) == "HInt")
		return new HInt();
	else if (GetArg(0) == "HString")
		return new HString(new QString(""));
	return new HBool(false);
}
H_MemberFunction_def(deleteclass, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	if (HMain->accessclass(GetArg(0)) == nullptr)
		return new HBool(false);
	HMain->deleteclass(GetArg(0));
	return new HBool(true);
}