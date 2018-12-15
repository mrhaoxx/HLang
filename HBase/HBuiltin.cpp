#include "HBuiltin.h"
#include <QMessageBox>
#include <iostream>
#include "HData/HVector.h"
#include "HLogic/HWhile.h"
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
	DefineMemberFunction(HBuiltin, "aboutQt", &HBuiltin::aboutQt);
	this->HDef = def;
}

QSharedPointer<HObject> HBuiltin::setdebug(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HBool);
	CheckArgsType(1, HBool);
	IS_DEBUG << "Setting debug message:" << "Debug?" << HObjectHelper(args[0]).to<HBool>()->value() << "Colorful?" << HObjectHelper(args[1]).to<HBool>()->value();
	*isdebug = HObjectHelper(args[0]).to<HBool>()->value();
	*iscolorful = HObjectHelper(args[1]).to<HBool>()->value();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HBuiltin::aboutQt(HArgs args)
{
	CheckArgs(0);
	QApplication::aboutQt();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HBuiltin::newclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	IS_DEBUG << "Building new class";
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "window")
		return QSharedPointer<HObject>((HObject*)new HWindow);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "pushbutton")
		return QSharedPointer<HObject>((HObject*)new HPushButton(nullptr));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "function")
		return QSharedPointer<HObject>(new HFunction(HDef));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "bool")
		return QSharedPointer<HObject>(new HBool);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "int")
		return QSharedPointer<HObject>(new HInt);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "string")
		return QSharedPointer<HObject>(new HString);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "if")
		return QSharedPointer<HObject>(new HIf);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "tcpsocket")
		return QSharedPointer<HObject>(new HTcpSocket);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "codes")
		return QSharedPointer<HObject>(new HCodes(HDef));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "vector")
		return QSharedPointer<HObject>(new HVector);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "while")
		return QSharedPointer<HObject>(new HWhile);
	throw HError(HError::RT_ERROR, WhyBuiltinNewFailed);
}
QSharedPointer<HObject> HBuiltin::deleteclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	HDef->deleteclass(HObjectHelper(args[0]).to<HString>()->toQString());
	return QSharedPointer<HObject>(new HVoid);
}
QSharedPointer<HObject> HBuiltin::sleep(HArgs args)
{
	CheckArgs(1);
	int usecs;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
		usecs = *HObjectHelper(args[0]).to<HInt>();
	else
		usecs = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	QThread::usleep(usecs);
	return QSharedPointer<HObject>(new HVoid);
}
QSharedPointer<HObject> HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	return QSharedPointer<HObject>(new HInt(std::system(*HObjectHelper(args[0]).to<HString>())));
}
QSharedPointer<HObject> HBuiltin::msg(HArgs args)
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
	return QSharedPointer<HObject>(new HVoid);
}
QSharedPointer<HObject> HBuiltin::cout(HArgs args) {
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
	return QSharedPointer<HObject>(new HVoid);
};

QSharedPointer<HObject> HBuiltin::termimate(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	exit(*HObjectHelper(args[0]).to<HInt>());
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HBuiltin::keepexec(HArgs args)
{
	CheckArgs(0);
	return QSharedPointer<HObject>(new HInt(QApplication::exec()));
}

QSharedPointer<HObject> HBuiltin::quit(HArgs args)
{
	CheckArgs(0);
	QApplication::quit();
	return QSharedPointer<HObject>(new HVoid);
}