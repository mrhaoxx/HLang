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
}

H_MemberFunction_def(add, HFunction)
{
	CheckArgs(1);
	SetupArgs;
	commands.push_back(HLangHelper::processcommand(GetArg(0)));
	return new HBool(true);
}
H_MemberFunction_def(hexec, HFunction)
{
	for (int i = 0; i < commands.length(); i++)
	{
		if (commands[i]->_self == nullptr)
			commands[i]->_self = new QString();
		if (commands[i]->_class == nullptr)
			commands[i]->_class = new QString();
		if (commands[i]->_func == nullptr)
			commands[i]->_func = new QString();
		if (commands[i]->_args == nullptr)
			commands[i]->_args = new QStringList();
		if (commands[i]->_backvalue_name == nullptr)
			if (HMain->accessclass(*commands[i]->_class) != nullptr)
				HMain->accessclass(*commands[i]->_class)->exec(*commands[i]->_func, *commands[i]->_self, *commands[i]->_args);
			else;
		else
			if (HMain->accessclass(*commands[i]->_class) != nullptr)
				HMain->importclass(*commands[i]->_backvalue_name, HMain->accessclass(*commands[i]->_class)->exec(*commands[i]->_func, *commands[i]->_self, *commands[i]->_args));
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
			commands.push_back(HLangHelper::processcommand(str));
	}
	return new HBool(true);
}