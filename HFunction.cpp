#include "HFunction.h"
#include "HLang.h"
#include <QFile>

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("loadfile", &HFunction::loadfile);
	DefineMemberFunction("toString", &HFunction::toString);
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
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		commands.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
		return new HBool(true);
	}
	return new HBool(false);
}
HObject* HFunction::hexec(HArgs args)
{
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i], def);
	}
	return new HBool(true);
}
HObject* HFunction::loadfile(HArgs args)
{
	CheckArgs(1);
	QString file_w = HObjectHelper(args[0]).to<HString>()->toQString();
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return new HBool(false);
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		if (QString(line).at(QString(line).length()) == "\n")
			line.chop(1);
		QString str(line);
		if (!str.isEmpty() && !(str.at(0) == "#"))
			commands.push_back(new QString(str));
	}
	return new HBool(true);
}

HObject* HFunction::toString(HArgs args)
{
	CheckArgs(0);
	QString cs;
	for (int i = 0; i < commands.length(); i++)
		cs.append(*commands[i] + "\r\n");
	return new HString(new QString(cs));
}

HObject* HFunction::loadString(HArgs args)
{
	return new HBool(false);
}