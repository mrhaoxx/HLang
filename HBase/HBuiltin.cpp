#include "HBuiltin.h"
#include <QMessageBox>
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

HPointer HBuiltin::setdebug(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HBool);
	CheckArgsType(1, HBool);
	IS_DEBUG << "Setting debug message:" << "Debug?" << HObjectHelper(args[0]).to<HBool>()->value() << "Colorful?" << HObjectHelper(args[1]).to<HBool>()->value();
	*isdebug = HObjectHelper(args[0]).to<HBool>()->value();
	*iscolorful = HObjectHelper(args[1]).to<HBool>()->value();
	return HPointer(new HVoid);
}

HPointer HBuiltin::aboutQt(HArgs args)
{
	CheckArgs(0);
	QApplication::aboutQt();
	return HPointer(new HVoid);
}

HPointer HBuiltin::newclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	IS_DEBUG << "Building new class";
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "window")
		return HPointer((HObject*)new HWindow);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "pushbutton")
		return HPointer((HObject*)new HPushButton(nullptr));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "function")
		return HPointer(new HFunction(HDef));
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "bool")
		return HPointer(new HBool);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "int")
		return HPointer(new HInt);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "string")
		return HPointer(new HString);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "if")
		return HPointer(new HIf);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "tcpsocket")
		return HPointer(new HTcpSocket);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "class") {
		HClass* p = new HClass(HDef);
		HPointer sp(p);
		p->setupthis(sp);
		return sp;
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "vector")
		return HPointer(new HVector);
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "while")
		return HPointer(new HWhile);
	throw HError(HError::RT_ERROR, WhyBuiltinNewFailed);
}
HPointer HBuiltin::deleteclass(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	HDef->deleteclass(HObjectHelper(args[0]).to<HString>()->toQString());
	return HPointer(new HVoid);
}
HPointer HBuiltin::sleep(HArgs args)
{
	CheckArgs(1);
	int usecs;
	if (HObjectHelper(args[0]).to<HInt>() != nullptr)
		usecs = *HObjectHelper(args[0]).to<HInt>();
	else
		usecs = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	QThread::usleep(usecs);
	return HPointer(new HVoid);
}
HPointer HBuiltin::system(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	return HPointer(new HInt(std::system(*HObjectHelper(args[0]).to<HString>())));
}
HPointer HBuiltin::msg(HArgs args)
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
	return HPointer(new HVoid);
}
HPointer HBuiltin::cout(HArgs args) {
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
	return HPointer(new HVoid);
};

HPointer HBuiltin::termimate(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	exit(*HObjectHelper(args[0]).to<HInt>());
	return HPointer(new HVoid);
}

HPointer HBuiltin::keepexec(HArgs args)
{
	CheckArgs(0);
	return HPointer(new HInt(QApplication::exec()));
}

HPointer HBuiltin::quit(HArgs args)
{
	CheckArgs(0);
	QApplication::quit();
	return HPointer(new HVoid);
}