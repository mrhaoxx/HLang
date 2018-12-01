#include "HLang.h"
#include <iostream>
#ifdef Has_Commandline_Front
#include "Front/commandline.h"
#endif
HLang::HLang(HLang* hl)
{
	this->higherlevel = hl;
}

HLang::~HLang()
{
	QMapIterator<QString, HObject*> i(classes);
	QStringList namelist;
	IS_DEBUG << "Destruction domain >>" << this << "<< {";
	for (; i.hasNext();)
	{
		i.next();
		namelist.append(i.key());
	}
	for (int i = 0; i < namelist.length(); i++)
	{
		deleteclass(namelist[i]);
	}
	IS_DEBUG << "} [OK]";
}

bool HLang::importclass(QString __name, HObject* __class)
{
	IS_DEBUG << ">>" << this << "<< Importing [" << __name.toStdString().c_str() << "]";
	if (classes.contains(__name))
		return false;
	if (__class == nullptr)
	{
		return false;
	}
	classes.insert(__name, __class);
	return true;
}
HObject* HLang::accessclass(QString __name)
{
	if (classes.contains(__name)) {
		IS_DEBUG << ">>" << this << "<< Accessing [" << __name.toStdString().c_str() << "]";
		return classes[__name];
	}
	if (higherlevel == nullptr) {
		IS_DEBUG << ">>" << this << "<< AccessingNotFound [" << __name.toStdString().c_str() << "]";
		return nullptr;
	}
	IS_DEBUG << ">>" << this << "<< AccessingRedirect[" << __name.toStdString().c_str() << "]->" << higherlevel;
	return higherlevel->accessclass(__name);
}

void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		IS_DEBUG << ">>" << this << "<< Deleting [" << __name.toStdString().c_str() << "]";
		delete classes[__name];
		classes.remove(__name);
		return;
	}
}
HCommand* HLangHelper::processcommand(QString command) {
}