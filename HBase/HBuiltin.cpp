#include "HBuiltin.h"
#include <QMessageBox>
#include <iostream>
HBuiltin::HBuiltin(HLang *def)
{
	DefineMemberFunction(HBuiltin, "new", &HBuiltin::newclass);
	DefineMemberFunction(HBuiltin, "delete", &HBuiltin::deleteclass);
	DefineMemberFunction(HBuiltin, "usleep", &HBuiltin::sleep);
	DefineMemberFunction(HBuiltin, "system", &HBuiltin::system);
	DefineMemberFunction(HBuiltin, "msg", &HBuiltin::msg);
	DefineMemberFunction(HBuiltin, "cout", &HBuiltin::cout);
	DefineMemberFunction(HBuiltin, "exec", &HBuiltin::keepexec);
	DefineMemberFunction(HBuiltin, "quit", &HBuiltin::quit);
	DefineMemberFunction(HBuiltin, "exit", &HBuiltin::termimate);
	DefineMemberFunction(HBuiltin, "setdebug", &HBuiltin::setdebug);
	this->HDef = def;
}

HObject* HBuiltin::setdebug(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HBool);
	CheckArgsType(1, HBool);
	IS_DEBUG << "Setting debug message:" << "Debug?" << HObjectHelper(args[0]).to<HBool>()->value() << "Colorful?" << HObjectHelper(args[1]).to<HBool>()->value();
	*isdebug = HObjectHelper(args[0]).to<HBool>()->value();
	*iscolorful = HObjectHelper(args[1]).to<HBool>()->value();
	return new HVoid;
}

HObject* HBuiltin::newclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	IS_DEBUG << "Building new class";
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "window")
		return (HObject*)new HWindow;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "PushButton")
		return (HObject*)new HPushButton(nullptr);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "function")
		return new HFunction(HDef);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "bool")
		return new HBool;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "int")
		return new HInt;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "string")
		return new HString;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "if")
		return new HIf;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "TcpSocket")
		return new HTcpSocket;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "codes")
		return new HCodes(HDef);
	throw HError(HError::RT_ERROR, WhyBuiltinNewFailed);
}
HObject* HBuiltin::deleteclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	HDef->deleteclass(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HVoid;
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
	return new HVoid;
}
HObject* HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);

	std::system((*HObjectHelper(args[0]).to<HString>()));
	return new HVoid;
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
		throw HError(HError::RT_ERROR, WhyBuiltinMsgFailed);
	return new HVoid;
}
HObject* HBuiltin::cout(HArgs args) {
	CheckArgs(1);
	bool iss = false;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
	{
		qDebug() << QString::number(*HObjectHelper(args[0]).to<HInt>());
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HBool>() != nullptr)
	{
		qDebug() << (HObjectHelper(args[0]).to<HBool>()->value());
		iss = true;
	}
	else if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		qDebug() << (const char*)(*HObjectHelper(args[0]).to<HString>());
	}
	if (!iss)
		throw HError(HError::RT_ERROR, WhyBuiltinMsgFailed);
	return new HVoid;
};

HObject* HBuiltin::termimate(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	exit(*HObjectHelper(args[0]).to<HInt>());
	return new HVoid;
}

HObject* HBuiltin::keepexec(HArgs args)
{
	CheckArgs(0);
	return new HInt(QApplication::exec());
}

HObject* HBuiltin::quit(HArgs args)
{
	CheckArgs(0);
	QApplication::quit();
	return new HVoid;
}

void HBuiltin::setDef(HLang* def)
{
	HDef = def;
}