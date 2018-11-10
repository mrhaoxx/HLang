#include "HBuiltin.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HFunction.h"
#include "HBool.h"
H_MemberFunction_def(newclass, HBuiltin)
{
	CheckArgs(2);
	SetupArgs;
	if (GetArg(0) == "HWindow")
	{
		HWindow *_class = new HWindow;
		if (HMain->importclass(GetArg(1), (HObject*)(_class)))
			return new HBool(true);
		delete _class;
	}
	else if (GetArg(0) == "HPushButton")
	{
		HPushButton *_class = new HPushButton(nullptr);
		if (HMain->importclass(GetArg(1), (HObject*)_class))
		{
			HMain->importclass(GetArg(1), (QWidget*)_class);
			return new HBool(true);
		}
		delete _class;
	}
	else if (GetArg(0) == "HFunction")
	{
		HFunction *_class = new HFunction;
		if (HMain->importclass(GetArg(1), (HObject*)_class))
		{
			return new HBool(true);
		}
		delete _class;
	}

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