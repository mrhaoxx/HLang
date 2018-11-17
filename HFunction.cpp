#include "HFunction.h"
#include "HLang.h"
#include <QFile>

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("loadfile", &HFunction::loadfile);
}

HFunction::~HFunction()
{
	for (int i = 0; i < commands.length(); i++)
	{
		delete commands[i];
	}
}

HObject* HFunction::add(std::vector<HObject*> args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		commands.push_back(new QString(HObjectHelper(args[0]).to<HString>()->toQString()));
		return new HBool(true);
	}
	return new HBool(false);
}
HObject* HFunction::hexec(std::vector<HObject*> args)
{
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i]);
	}
	return new HBool(true);
}
HObject* HFunction::loadfile(std::vector<HObject*> args)
{
	CheckArgs(1);
	QString file_w = HObjectHelper(args[0]).to<HString>()->toQString();
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return new HBool(false);
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		line.chop(1);
		QString str(line);
		if (!str.isEmpty() && !(str.at(0) == "#"))
			commands.push_back(new QString(str));
	}
	return new HBool(true);
}