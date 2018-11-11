#include "HFunction.h"
#include "HBaseInterface.h"
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

H_MemberFunction_def(add, HFunction)
{
	CheckArgs(1);
	SetupArgs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HString*) != nullptr)
	{
		commands.push_back(new QString(HObjTo(HMain->accessclass(GetArg(0)), HString*)->toQString()));
		return new HBool(true);
	}
	return new HBool(false);
}
H_MemberFunction_def(hexec, HFunction)
{
	for (int i = 0; i < commands.length(); i++)
	{
		HLangHelper::exec(*commands[i]);
	}
	return new HBool(true);
}
H_MemberFunction_def(loadfile, HFunction)
{
	CheckArgs(1);
	SetupArgs;
	QString file_w = GetArg(0);
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