#include "HLang.h"
#include "HString.h"
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

HCommand* HLangHelper::processcommand(QString command, HLang *def) {
	QStringList t;
	if (command.count("\"") == 2)
	{
		t = command.split("\"");
		def->importclass("tmp-processing" + command.at(0).toLatin1() + command.at(command.length()).toLatin1(), new HString(new QString(t[1])));
		t[1] == "tmp-processing" + command.at(0).toLatin1() + command.at(command.length()).toLatin1();
		command = t.join("");
	}
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
	else
	{
		c->_class = new QString("builtin");
		if (command.contains("=")) {
			c->_backvalue_name = new QString(command.split("=").at(0).trimmed());
			command = QString(command.split("=").mid(1).join("=").trimmed());
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
bool HLangHelper::exec(QString command, HLang *def)
{
	int tr = 0;
	std::vector<int> usedtr;
	QStringList t = command.split("\"");
	while (t.length() >= 2)
	{
		while (!def->importclass("tmp-processing-" + QString::number(tr), new HString(new QString(t[1]))))
			tr++;
		usedtr.push_back(tr);
		t[1] = "tmp-processing-" + QString::number(tr);
		command = t.join("");
		t = command.split("\"");
	}
	HCommand *c = HLangHelper::processcommand(command, def);
	if (c->_self == nullptr)
		c->_self = new QString();
	if (c->_class == nullptr)
		c->_class = new QString("builtin");
	if (c->_func == nullptr)
		c->_func = new QString();
	if (c->_args == nullptr)
		c->_args = new QStringList();
	HArgs vec;
	for (int i = 0; i < c->_args->length(); i++)
		if (def->accessclass(c->_args->at(i)) != nullptr)
			vec.push_back(def->accessclass(c->_args->at(i)));

	if ((def->accessclass(*(c->_class))) != nullptr)
	{
		if (c->_backvalue_name == nullptr)
			def->accessclass(*(c->_class))->exec(*(c->_func), vec);
		else
		{
			def->importclass(*(c->_backvalue_name), def->accessclass(*(c->_class))->exec(*(c->_func), vec));
		}
	}
	else
	{
		for (int i = 0; i < usedtr.size(); i++)
			def->deleteclass("tmp-processing-" + QString::number(usedtr[i]));
		return false;
	}
	for (int i = 0; i < usedtr.size(); i++)
		def->deleteclass("tmp-processing-" + QString::number(usedtr[i]));
	return true;
}