#include "HLang.h"
bool HLang::import(HString __name, HObject* __class)
{
	if (classes.contains(__name))
		return false;
	classes.insert(__name, __class);
	return true;
}
bool HLang::import(HString __name, QWidget * __class)
{
	if (QGuiClasses.contains(__name))
		return false;
	QGuiClasses.insert(__name, __class);
	return true;
}
bool HLang::import(HString __name, HOBJECTS * __objs)
{
	if (varrs.contains(__name))
		return false;
	varrs.insert(__name, __objs);
	return true;
}
HObject* HLang::accessclass(HString __name)
{
	if (classes.contains(__name))
		return classes[__name];
	return nullptr;
}

HOBJECTS * HLang::accessvarrs(HString __name)
{
	if (varrs.contains(__name))
		return varrs[__name];
	return nullptr;
}

QWidget * HLang::accessQGuiclass(HString __name)
{
	if (QGuiClasses.contains(__name))
		return QGuiClasses[__name];
	return nullptr;
}

void HLang::deleteclass(HString __name)
{
	if (classes.contains(__name))
	{
		delete classes[__name];
		classes.remove(__name);
		if (QGuiClasses.contains(__name))
			QGuiClasses.remove(__name);
	}
}