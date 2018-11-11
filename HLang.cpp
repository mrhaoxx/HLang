#include "HLang.h"
bool HLang::importclass(QString __name, HObject* __class)
{
	if (classes.contains(__name))
		return false;
	classes.insert(__name, __class);
	return true;
}
HObject* HLang::accessclass(QString __name)
{
	if (classes.contains(__name))
		return classes[__name];
	return nullptr;
}

void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		delete classes[__name];
		classes.remove(__name);
	}
}
namespace HLangHelper {
	HCommand* processcommand(QString command) {
		HCommand *c = new HCommand;
		if (command.contains("."))
		{
			c->_class = new QString(command.split(".")[0]);
			command = command.split(".").mid(1).join(".");
			if (c->_class->contains("=")) {
				c->_backvalue_name = new QString(c->_class->split("=").at(0).trimmed());
				c->_class = new QString(c->_class->split("=").at(1).trimmed());
			}
		}
		if (command.contains("("))
		{
			c->_func = new QString(command.split("(")[0]);
			command = command.split("(").mid(1).join("(");
		}
		if (command.contains(")"))
		{
			QStringList _t = command.split(")");
			_t.removeLast();
			command = _t.join(")");
		}
		if (command.contains(","))
		{
			c->_args = new QStringList(command.split(","));
		}
		else
		{
			c->_args = new QStringList(command);
		}
		return c;
	}
}