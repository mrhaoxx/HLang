#include "HBuiltin.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HBaseInterface.h"
#ifdef WIN32
#include "windows.h"
#define ALsleep Sleep
#endif
#ifdef LINUX
#include <unistd.h>
#define ALsleep usleep
#endif
#ifdef H_DEBUG
#include <QDebug>
#endif

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
	else if (GetArg(0) == "HIf")
		return new HIf();
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

H_MemberFunction_def(hsleep, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	int usecs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HInt*) != nullptr)
		usecs = *HObjTo(HMain->accessclass(GetArg(0)), HInt*)->value();
	else
		usecs = GetArg(0).toInt();
	ALsleep(usecs);
	return new HBool(true);
}
#ifdef H_DEBUG
H_MemberFunction_def(hcout, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	HObject* obj = HMain->accessclass(GetArg(0));
	if (HObjTo(obj, HInt*) != nullptr)
		qDebug() << *(HObjTo(obj, HInt*)->value());
	else if (HObjTo(obj, HBool*) != nullptr)
		qDebug() << HObjTo(obj, HBool*)->value();
	else if (HObjTo(obj, HString*) != nullptr)
		qDebug() << HObjTo(obj, HString*)->toQString();
	return new HBool(true);
}
#endif