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
	int tmpused = 0;

private:
	HClassMap classes;
};
extern HLang* HMain;
namespace HLangHelper {
	HCommand* processcommand(QString command);
	bool exec(QString command, HLang *def = HMain, commandline *cm = nullptr);
}
