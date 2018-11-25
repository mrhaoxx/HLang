#include "HFunction.h"
#include <QFile>

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("loadfile", &HFunction::loadfile);
	DefineMemberFunction("toString", &HFunction::toString);
	DefineMemberFunction("addArgs", &HFunction::addArgs);
	DefineMemberFunction("link", &HFunction::link);
	DefineMemberFunction("fromString", &HFunction::fromString);
	HBuiltin *but = new HBuiltin;
	but->HDef = def;
	def->importclass("builtin", but);
	def->importclass("thisfunction", this);
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
	commands.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
	return new HRet(true);
}

HObject* HFunction::loadfile(HArgs args)
{
	CheckArgs(1);
	QString file_w = HObjectHelper(args[0]).to<HString>()->toQString();
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return new HRet(nullptr, false, WhyFunctionLoadFileFailed);
	while (!file.atEnd()) {
		QString str = file.readAll();
		QStringList strlist = str.split(";");
		for (int i = 0; i < strlist.length(); i++)
			strlist[i] = strlist[i].simplified();
		for (int i = 0; i < strlist.length(); i++)
		{
			if (!strlist[i].isEmpty() && !(strlist[i].at(0) == "#"))
				commands.push_back(new QString(strlist[i]));
		}
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

HObject* HFunction::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	QString str = HObjectHelper(args[0]).to<HString>()->toQString();
	QStringList strlist = str.split(";");
	for (int i = 0; i < strlist.length(); i++)
		strlist[i] = strlist[i].simplified();
	for (int i = 0; i < strlist.length(); i++)
	{
		if (!strlist[i].isEmpty() && !(strlist[i].at(0) == "#"))
			commands.push_back(new QString(strlist[i]));
	}
	return new HRet(true);
}

HObject* HFunction::addArgs(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	argsname.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
	return new HRet(true);
}

HObject* HFunction::link(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HObject);
	def->importclass(HObjectHelper(args[0]).to<HString>()->toQString(), args[1]);
	return new HRet(true);
}

void HFunction::reset()
{
	def = new HLang;
	def->importclass("builtin", new HBuiltin);
	return;
}

HObject* HFunction::hexec(HArgs args)
{
	CheckArgs((int)argsname.size());
	if (!args.isEmpty())
		def->importclass("this", args[0]);
	for (int i = 1; i < (int)argsname.size() - 1; i++)
		def->importclass(*argsname[i], args[i]);
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i], def);
	}
	this->reset();
	return new HRet(true);
}