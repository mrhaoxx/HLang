#include "HLang.h"
#include "HString.h"
#include <iostream>
#ifdef Has_Commandline_Front
#include "Front/commandline.h"
#endif
HLang::~HLang()
{
	for (int i = 0; i < registeredclasses.length(); i++)
	{
		deleteclass(registeredclasses[i]);
	}
}

bool HLang::importclass(QString __name, HObject* __class)
{
	if (classes.contains(__name))
		return false;
	classes.insert(__name, __class);
	registeredclasses.push_front(__name);
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
HCommand* HLangHelper::processcommand(QString command) {
	QStringList t;
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
bool HLangHelper::exec(QString cd, HLang *def, commandline *cm)
{
	QString command = cd;
	QStringList t = command.split("\"");
	command.clear();
	if (t.length() >= 2)
	{
		QString tmp;
		for (int i = 1; i < t.length() - 1; i++)
			tmp.append(t[i] + ((i != (t.length() - 2)) ? "\"" : ""));
		for (int i = 1; i < t.length() - 1; i++)
			t.removeAt(1);
		while (!def->importclass("tmp-processing-" + QString::number(def->tmpused), new HString(new QString(tmp))))
			def->tmpused++;
		if (t.length() != 3)
			t.insert(1, "tmp-processing-" + QString::number(def->tmpused));
		else
			t[1] = "tmp-processing-" + QString::number(def->tmpused);
		command = t.join("");
	}
	else
		command = t.join("\"");
	HCommand *c = HLangHelper::processcommand(command);
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
		HRet *ret;

		ret = HObjectHelper(def->accessclass(*(c->_class))->exec(*(c->_func), vec)).to<HRet>();
		if (ret->getSuccess())
		{
			if (c->_backvalue_name != nullptr)
				def->importclass(*(c->_backvalue_name), ret->getObject());
		}
#ifdef Has_Commandline_Front
		if (cm == nullptr)
			qDebug() << def << "[" + (ret->getSuccess() ? QString("OK") : QString("Failed")) + "]{" + cd.simplified() + "} " + ret->getReason().simplified();
		else
			cm->add("[" + (ret->getSuccess() ? QString("OK") : QString("Failed")) + "]" + ret->getReason().simplified());
#else
		qDebug() << def << "[" + (ret->getSuccess() ? QString("OK") : QString("Failed")) + "]{" + cd.simplified() + "} " + ret->getReason().simplified();
#endif
		delete ret;
	}
	else
	{
#ifdef Has_Commandline_Front
		if (cm == nullptr)
			qDebug() << def << "[Failed]{" + cd + "} Class Not Find";
		else
			cm->add("[Failed]Class Not Find");
#else
		qDebug() << def << "[Failed]{" + cd + "} Class Not Find";
#endif
		return false;
	}
	return true;
}