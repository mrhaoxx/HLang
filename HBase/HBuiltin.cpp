#include "HBuiltin.h"
#include <QMessageBox>
#ifdef WIN32
#include "windows.h"
#define ALsleep Sleep
#endif
#ifndef WIN32
#include <unistd.h>
#define ALsleep usleep
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
	CheckArgsType(0, HString);
	std::string str = "123";
	if (HObjectHelper(args[0]) == "Window")
		return new HRet((HObject*)new HWindow);
	else if (HObjectHelper(args[0]) == "PushButton")
		return new HRet((HObject*)new HPushButton(nullptr));
	else if (HObjectHelper(args[0]) == "function")
		return new HRet(new HFunction);
	else if (HObjectHelper(args[0]) == "bool")
		return new HRet(new HBool);
	else if (HObjectHelper(args[0]) == "int")
		return new HRet(new HInt);
	else if (HObjectHelper(args[0]) == "string")
		return new HRet(new HString);
	else if (HObjectHelper(args[0]) == "if")
		return new HRet(new HIf);
	else if (HObjectHelper(args[0]) == "TcpSocket")
		return new HRet(new HTcpSocket);
	return new HRet(nullptr, false, WhyBuiltinNewFailed);
}
HObject* HBuiltin::deleteclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	HDef->deleteclass(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HRet(true);
}
HObject* HBuiltin::sleep(HArgs args)
{
	CheckArgs(1);
	int usecs;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
		usecs = HObjectHelper(args[0]);
	else
		usecs = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	ALsleep(usecs);
	return new HRet(true);
}
HObject* HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);

	std::system(HObjectHelper(args[0]).to<HString>()->toQString().toStdString().c_str());
	return new HRet(true);
}
HObject* HBuiltin::msg(HArgs args)
{
	CheckArgs(1);
	bool iss = false;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", QString::number(HObjectHelper(args[0])));
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HBool>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", (HObjectHelper(args[0])) ? QString("true") : QString("false"));
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", HObjectHelper(args[0]));
		iss = true;
	}
	if (!iss)
		return new HRet(nullptr, iss, WhyBuiltinMsgFailed);
	return new HRet(iss);
}