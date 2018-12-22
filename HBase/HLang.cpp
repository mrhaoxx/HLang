#include "HLang.h"
#include <iostream>
HLang::HLang(HLang* hl)
{
	this->higherlevel = hl;
}

HLang::~HLang()
{
	QMapIterator<QString, HPointer> i(classes);
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

bool HLang::importclass(QString __name, HPointer __class)
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
HWeakPointer HLang::accessclass(QString __name)
{
	if (classes.contains(__name)) {
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Accessing [" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		if (classes[__name])
			return classes[__name];
		else
			classes.remove(__name);
	}
	if (higherlevel == nullptr) {
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "AccessingNotFound [" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		return HWeakPointer(nullptr);
	}
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "AccessingRedirect[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]->" << higherlevel;
	return higherlevel->accessclass(__name);
}

void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "Deleting" << ColorClear << "[" << PURPLECOLOR << __name.toStdString().c_str() << ColorClear << "]";
		classes[__name].clear();
		classes.remove(__name);
		return;
	}
}

QMap<QString, HPointer>* HLang::dr()
{
	return &classes;
}