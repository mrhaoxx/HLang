#pragma once

#include "HObject.h"
#include <QWidget>
class HLang
{
public:
	bool import(HString __name, HObject* __class);
	bool import(HString __name, QWidget* __class);
	bool import(HString __name, HOBJECTS* __objs);
	HObject* accessclass(HString __name);
	HOBJECTS* accessvarrs(HString __name);
	QWidget* accessQGuiclass(HString __name);
	void deleteclass(HString __name);
private:
	HVarrMap varrs;
	HClassMap classes;
	QGuiClassMap QGuiClasses;
};

extern HLang* HMain;