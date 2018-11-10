#include "HFunction.h"
#include "HLang.h"
#include <QFile>
#include "HBool.h"

HFunction::HFunction()
{
	DefineMemberFunction("add", &HFunction::add);
	DefineMemberFunction("exec", &HFunction::hexec);
	DefineMemberFunction("readfile", &HFunction::readfile);
}

HFunction::~HFunction()
{
}

H_MemberFunction_def(add, HFunction)
{
	CheckArgs(5);
	SetupArgs;
	HCommand *c = new HCommand;
	c->_class = GetArg(0);
	c->_func = GetArg(1);
	c->_self = GetArg(2);
	c->_backvalue_name = GetArg(3);
	c->_args = args.mid(4);
	commands.push_back(c);
	return new HBool(true);
}
H_MemberFunction_def(hexec, HFunction)
{
	for (int i = 0; i < commands.length(); i++)
	{
		if (commands[i]->_backvalue_name.isNull())
			if (HMain->accessclass(commands[i]->_class) != nullptr)
				HMain->accessclass(commands[i]->_class)->exec(commands[i]->_func, commands[i]->_self, commands[i]->_args);
			else;
		else
			if (HMain->accessclass(commands[i]->_class) != nullptr)
				HMain->importclass(commands[i]->_backvalue_name, HMain->accessclass(commands[i]->_class)->exec(commands[i]->_func, commands[i]->_self, commands[i]->_args));
	}
	return new HBool(true);
}
H_MemberFunction_def(readfile, HFunction)
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
		QStringList list = str.split(" ");
		this->add(HOBJECTS(), HOBJECTS(list));
	}
	return new HBool(true);
}