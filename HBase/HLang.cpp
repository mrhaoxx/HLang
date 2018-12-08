#include "HLang.h"
#include <iostream>
HLang::HLang(HLang* hl)
{
	this->higherlevel = hl;
}

HLang::~HLang()
{
	QMapIterator<QString, HObject*> i(classes);
	QStringList namelist;
	IS_DEBUG << REDCOLOR << "Destruction domain" << ColorClear << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<< {";
	IndentAdd;
	for (; i.hasNext();)
	{
		i.next();
		namelist.append(i.key());
	}
	for (int i = 0; i < namelist.length(); i++)
	{
		deleteclass(namelist[i]);
	}
	IndentRem;
	IS_DEBUG << "}" << BULECOLOR << "[OK]" << ColorClear;
}

bool HLang::importclass(QString __name, HObject* __class)
{
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<< " << YELLOWCOLOR << "Importing[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
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
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Accessing [" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		return classes[__name];
	}
	if (higherlevel == nullptr) {
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "AccessingNotFound [" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		return nullptr;
	}
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "AccessingRedirect[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]->" << higherlevel;
	return higherlevel->accessclass(__name);
}

void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "Deleting" << ColorClear << "[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		delete classes[__name];
		classes.remove(__name);
		return;
	}
}

void HLang::IgnClass(QString __name)
{
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "Ignoring" << ColorClear << "[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
	classes.remove(__name);
}