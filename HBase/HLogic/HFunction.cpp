#include "HFunction.h"
#include <QFile>

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("loadfile", &HFunction::loadfile);
	DefineMemberFunction("toString", &HFunction::toString);
	DefineMemberFunction("addArgs", &HFunction::addArgs);
	HBuiltin *but = new HBuiltin;
	but->HDef = def;
	def->importclass("builtin", but);
}

HFunction::~HFunction()
{
	for (int i = 0; i < commands.length(); i++)
	{
		delete commands[i];
	}
	delete def;
}

HObject* HFunction::add(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		commands.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
		return new HRet(true);
	}
	return new HRet(nullptr, false, WhyFunctionAddFailed);
}

HObject* HFunction::loadfile(HArgs args)
{
	CheckArgs(1);
	QString file_w = HObjectHelper(args[0]).to<HString>()->toQString();
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return new HRet(nullptr, false, WhyFunctionLoadFileFailed);
	while (!file.atEnd()) {
		QString str = file.readLine();
		str = str.simplified();
		if (!str.isEmpty() && !(str.at(0) == "#"))
			commands.push_back(new QString(str));
	}
	return new HRet(true);
}

HObject* HFunction::toString(HArgs args)
{
	CheckArgs(0);
	QString cs;
	for (int i = 0; i < commands.length(); i++)
		cs.append(*commands[i] + "\r\n");
	return new HRet(new HString(new QString(cs)));
}
HObject* HFunction::addArgs(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	argsname.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
	return new HRet(true);
}

HObject* HFunction::hexec(HArgs args)
{
	CheckArgs((int)argsname.size());
	for (int i = 0; i < argsname.size(); i++)
		def->importclass(*argsname[i], args[i]);
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i], def);
	}
	return new HRet(true);
}