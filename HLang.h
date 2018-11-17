#pragma once

#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
#include "HBaseInterface.h"
class HLang
{
public:
	bool importclass(QString __name, HObject* __class);
	HObject* accessclass(QString __name);
	void deleteclass(QString __name);
private:
	HClassMap classes;
};
extern HLang* HMain;
namespace HLangHelper {
	HCommand* processcommand(QString command, HLang *def = HMain);
	bool exec(QString command, HLang *def = HMain, commandline *cm = nullptr);
}
