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
	IS_DEBUG << ERRORCOLOR << "Destruction domain" << ColorClean << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<< {";
	for (; i.hasNext();)
	{
		i.next();
		namelist.append(i.key());
	}
	for (int i = 0; i < namelist.length(); i++)
	{
		deleteclass(namelist[i]);
	}
	IS_DEBUG << "}" << DONECOLOR << "[OK]" << ColorClean;
}

bool HLang::importclass(QString __name, HObject* __class)
{
	IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<< " << NOTICECOLOR << "Importing[" << CLASSCOLOR << __name.toStdString().c_str() << ColorClean << "]";
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
		IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "Accessing [" << CLASSCOLOR << __name.toStdString().c_str() << ColorClean << "]";
		return classes[__name];
	}
	if (higherlevel == nullptr) {
		IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << ERRORCOLOR << "AccessingNotFound [" << CLASSCOLOR << __name.toStdString().c_str() << ColorClean << "]";
		return nullptr;
	}
	IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "AccessingRedirect[" << CLASSCOLOR << __name.toStdString().c_str() << ColorClean << "]->" << higherlevel;
	return higherlevel->accessclass(__name);
}

void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << ERRORCOLOR << "Deleting" << ColorClean << "[" << CLASSCOLOR << __name.toStdString().c_str() << ColorClean << "]";
		delete classes[__name];
		classes.remove(__name);
		return;
	}
}