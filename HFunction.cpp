#include "HFunction.h"
#include "HLang.h"
#include <QFile>

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
	HCommand *c = new HCommand;
	c->_class = __arglist.toStringList().at(0);
	c->_func = __arglist.toStringList().at(1);
	c->_self = __arglist.toStringList().at(2);
	c->_backvalue_name = __arglist.toStringList().at(3);
	c->_args = __arglist.toStringList().mid(4);
	commands.push_back(c);
	return HOBJECTS(true);
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
				HMain->import(commands[i]->_backvalue_name, new HOBJECTS(HMain->accessclass(commands[i]->_class)->exec(commands[i]->_func, commands[i]->_self, commands[i]->_args)));
	}
	return HOBJECTS(true);
}
H_MemberFunction_def(readfile, HFunction)
{
	CheckArgs(1);
	QString file_w = __arglist.toStringList().at(0);
	QFile file(file_w);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return HOBJECTS(false);
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		line.chop(1);
		QString str(line);
		QStringList list = str.split(" ");
		this->add(HOBJECTS(), HOBJECTS(list));
	}
	return HOBJECTS(true);
}