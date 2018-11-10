#include "HLang.h"
bool HLang::importclass(QString __name, HObject* __class)
{
	if (classes.contains(__name))
		return false;
	classes.insert(__name, __class);
	return true;
}
bool HLang::importclass(QString __name, QWidget * __class)
{
	if (QGuiClasses.contains(__name))
		return false;
	QGuiClasses.insert(__name, __class);
	return true;
}
HObject* HLang::accessclass(QString __name)
{
	if (classes.contains(__name))
		return classes[__name];
	return nullptr;
}

QWidget * HLang::accessQGuiclass(QString __name)
{
	if (QGuiClasses.contains(__name))
		return QGuiClasses[__name];
	return nullptr;
}
void HLang::deleteclass(QString __name)
{
	if (classes.contains(__name))
	{
		delete classes[__name];
		classes.remove(__name);
		if (QGuiClasses.contains(__name))
			QGuiClasses.remove(__name);
	}
}