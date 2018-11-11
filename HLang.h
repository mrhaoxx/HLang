#pragma once

#include "HObject.h"
#include <QWidget>
#include <QString>
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
	HCommand *processcommand(QString command);
}
extern HLang* HMain;