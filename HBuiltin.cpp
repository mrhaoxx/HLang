#include "HBuiltin.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HBaseInterface.h"
#include <QMessageBox>
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
	if (GetArg(0) == "Window")
		return (HObject*)new HWindow;
	else if (GetArg(0) == "PushButton")
		return (HObject*)new HPushButton(nullptr);
	else if (GetArg(0) == "function")
		return new HFunction;
	else if (GetArg(0) == "bool")
		return new HBool;
	else if (GetArg(0) == "int")
		return new HInt;
	else if (GetArg(0) == "string")
		return new HString;
	else if (GetArg(0) == "if")
		return new HIf;
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
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HInt>() != nullptr)
		usecs = *HLangHelper(HMain->accessclass(GetArg(0))).to<HInt>()->value();
	else
		usecs = GetArg(0).toInt();
	ALsleep(usecs);
	return new HBool(true);
}
H_MemberFunction_def(hsystem, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HString>() != nullptr)
	{
		system(HLangHelper(HMain->accessclass(GetArg(0))).to<HString>()->toQString().toStdString().c_str());
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}
H_MemberFunction_def(msg, HBuiltin)
{
	CheckArgs(1);
	SetupArgs;
	HObject* obj = HMain->accessclass(GetArg(0));
	if (HLangHelper(obj).to<HInt>() != nullptr)
		QMessageBox::information(nullptr, "Message", QString::number(*HLangHelper(obj).to<HInt>()->value()));
	else if (HLangHelper(obj).to<HBool>() != nullptr)
		QMessageBox::information(nullptr, "Message", (HLangHelper(obj).to<HBool>()->value()) ? QString("true") : QString("false"));
	else if (HLangHelper(obj).to<HString>() != nullptr)
		QMessageBox::information(nullptr, "Message", HLangHelper(obj).to<HString>()->toQString());
	return new HBool(true);
}