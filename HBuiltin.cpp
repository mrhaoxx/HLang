#include "HBuiltin.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HFunction.h"
H_MemberFunction_def(newclass, HBuiltin)
{
	CheckArgs(2);
	if (__arglist.toStringList().at(0) == "HWindow")
	{
		HWindow *_class = new HWindow;
		if (HMain->import(__arglist.toStringList().at(1), (HObject*)(_class)))
			return HOBJECTS(true);
		delete _class;
	}
	else if (__arglist.toStringList().at(0) == "HPushButton")
	{
		HPushButton *_class = new HPushButton(nullptr);
		if (HMain->import(__arglist.toStringList().at(1), (HObject*)_class))
		{
			HMain->import(__arglist.toStringList().at(1), (QWidget*)_class);
			return HOBJECTS(true);
		}
		delete _class;
	}
	else if (__arglist.toStringList().at(0) == "HFunction")
	{
		HFunction *_class = new HFunction;
		if (HMain->import(__arglist.toStringList().at(1), (HObject*)_class))
		{
			return HOBJECTS(true);
		}
		delete _class;
	}
	return HOBJECTS(false);
}
H_MemberFunction_def(showvarrs, HBuiltin)
{
	CheckArgs(1);
	return IsVarrsToObj(__arglist.toStringList().at(0));
}
H_MemberFunction_def(newvarrs, HBuiltin)
{
	CheckArgs(2);
	if (HMain->import(__arglist.toStringList().at(0), new HOBJECTS(__arglist.toStringList().at(1))))
		return HOBJECTS(true);
	return HOBJECTS(false);
}
H_MemberFunction_def(deleteclass, HBuiltin)
{
	CheckArgs(1);
	if (HMain->accessclass(__arglist.toStringList().at(0)) == nullptr)
		return HOBJECTS(false);
	HMain->deleteclass(__arglist.toStringList().at(0));
	return HOBJECTS(true);
}