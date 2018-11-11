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
	HCommand processcommand(QString command) {
		HCommand c;
		if (command.contains("=")) {
			c._backvalue_name = QString(command.split("=").at(0).trimmed());
			command = command.split("=").at(1).trimmed();
		}
		if (command.contains("."))
		{
			c._class = QString(command.split(".").at(0).trimmed());
			command = command.split(".").at(1).trimmed();
		}
		if (command.contains("("))
		{
			c._func = QString(command.split("(").at(0).trimmed());
			command = command.split("(").at(1).trimmed();
		}
		if (command.contains(")"))
		{
			command = command.split(")").at(0).trimmed();
		}
		if (command.contains(","))
		{
			c._args = QStringList(command.split(","));
		}
		else
		{
			c._args = QStringList(command);
		}
		return c;
	}
}