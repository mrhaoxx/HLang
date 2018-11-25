#include "HBuiltin.h"
#include <QMessageBox>
#include <iostream>
HBuiltin::HBuiltin()
{
	DefineMemberFunction("new", &HBuiltin::newclass);
	DefineMemberFunction("delete", &HBuiltin::deleteclass);
	DefineMemberFunction("usleep", &HBuiltin::sleep);
	DefineMemberFunction("system", &HBuiltin::system);
	DefineMemberFunction("msg", &HBuiltin::msg);
	DefineMemberFunction("cout", &HBuiltin::cout);
	DefineMemberFunction("exit", &HBuiltin::termimate);
}

HObject* HBuiltin::newclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "window")
		return new HRet((HObject*)new HWindow);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "PushButton")
		return new HRet((HObject*)new HPushButton(nullptr));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "function")
		return new HRet(new HFunction);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "bool")
		return new HRet(new HBool);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "int")
		return new HRet(new HInt);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "string")
		return new HRet(new HString);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "if")
		return new HRet(new HIf);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "TcpSocket")
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
		usecs = *HObjectHelper(args[0]).to<HInt>();
	else
		usecs = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	QThread::usleep(usecs);
	return new HRet(true);
}
HObject* HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);

	std::system((*HObjectHelper(args[0]).to<HString>()));
	return new HRet(true);
}
HObject* HBuiltin::msg(HArgs args)
{
	CheckArgs(1);
	bool iss = false;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", QString::number(*HObjectHelper(args[0]).to<HInt>()));
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HBool>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", (*HObjectHelper(args[0]).to<HBool>()) ? QString("true") : QString("false"));
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		QMessageBox::information(nullptr, "Message", (*HObjectHelper(args[0]).to<HString>()));
		iss = true;
	}
	if (!iss)
		return new HRet(nullptr, iss, WhyBuiltinMsgFailed);
	return new HRet(iss);
}
HObject* HBuiltin::cout(HArgs args) {
	CheckArgs(1);
	bool iss = false;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
	{
		qDebug() << "ConsoleOutput{" << "\n" << QString::number(*HObjectHelper(args[0]).to<HInt>()) << "\n" << "}";
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HBool>() != nullptr)
	{
		qDebug() << "ConsoleOutput{" << "\n" << (HObjectHelper(args[0]).to<HBool>()->value()) << "\n" << "}";
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		qDebug() << "ConsoleOutput{" << "\n" << (const char*)(*HObjectHelper(args[0]).to<HString>()) << "\n" << "}";
		iss = true;
	}
	if (!iss)
		return new HRet(nullptr, iss, WhyBuiltinMsgFailed);
	qDebug() << "\r\n";
	return new HRet(iss);
};

HObject* HBuiltin::termimate(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	exit(*HObjectHelper(args[0]).to<HInt>());
	return new HRet(true);
}