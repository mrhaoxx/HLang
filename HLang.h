#pragma once

#include "HObject.h"
#include <QWidget>
#include <QString>
class HLang
{
public:
	bool importclass(QString __name, HObject* __class);
	bool importclass(QString __name, QWidget* __class);
	HObject* accessclass(QString __name);
	QWidget* accessQGuiclass(QString __name);
	void deleteclass(QString __name);
private:
	HClassMap classes;
	QGuiClassMap QGuiClasses;
};

extern HLang* HMain;