#pragma once

#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
#include "HData/HBool.h"
#include "HData/HInt.h"
#include "HData/HString.h"
#ifdef Has_Commandline_Front
class commandline;
#endif
class HLang
{
public:
	~HLang();
	bool importclass(QString __name, HObject* __class);
	HObject* accessclass(QString __name);
	void deleteclass(QString __name);
	int tmpused = 0;

private:
	QVector<QString> registeredclasses;
	HClassMap classes;
};
extern HLang* HMain;
namespace HLangHelper {
	HCommand* processcommand(QString command);
	bool exec(QString command, HLang *def = HMain, commandline *cm = nullptr);
}
