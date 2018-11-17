#include "HBuiltin.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HBaseInterface.h"
#include "HLang.h"
#include "HFunction.h"
#include "HIf.h"
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

HBuiltin::HBuiltin()
{
	DefineMemberFunction("new", &HBuiltin::newclass);
	DefineMemberFunction("delete", &HBuiltin::deleteclass);
	DefineMemberFunction("usleep", &HBuiltin::sleep);
	DefineMemberFunction("system", &HBuiltin::system);
	DefineMemberFunction("msg", &HBuiltin::msg);
}

HObject* HBuiltin::newclass(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "Window")
		return (HObject*)new HWindow;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "PushButton")
		return (HObject*)new HPushButton(nullptr);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "function")
		return new HFunction;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "bool")
		return new HBool;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "int")
		return new HInt;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "string")
		return new HString;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "if")
		return new HIf;
	return new HBool(false);
}
HObject* HBuiltin::deleteclass(HArgs args)
{
	CheckArgs(1);
	if (args[0] == nullptr)
		return new HBool(false);
	HMain->deleteclass(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HBool(true);
}
HObject* HBuiltin::sleep(HArgs args)
{
	CheckArgs(1);
	int usecs;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
		usecs = *HObjectHelper(args[0]).to<HInt>()->value();
	else
		usecs = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	ALsleep(usecs);
	return new HBool(true);
}
HObject* HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		std::system(HObjectHelper(args[0]).to<HString>()->toQString().toStdString().c_str());
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}
HObject* HBuiltin::msg(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
		QMessageBox::information(nullptr, "Message", QString::number(*HObjectHelper(args[0]).to<HInt>()->value()));
	else if (HObjectHelper(args[0]).to<HBool>() != nullptr)
		QMessageBox::information(nullptr, "Message", (HObjectHelper(args[0]).to<HBool>()->value()) ? QString("true") : QString("false"));
	else if (HObjectHelper(args[0]).to<HString>() != nullptr)
		QMessageBox::information(nullptr, "Message", HObjectHelper(args[0]).to<HString>()->toQString());
	return new HBool(true);
}