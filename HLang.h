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
namespace HLangHelper {
	HCommand* processcommand(QString command);
	bool exec(QString command);
}
extern HLang* HMain;
