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
class HLangHelper {
public:
	HLangHelper(HObject* obj);
	HLangHelper(HObject* obj[]);
	int length();
	static HCommand *processcommand(QString command);
	static bool exec(QString command);
	template<typename _Target>
	_Target* to()
	{
		if (iscoverable)
			return dynamic_cast<_Target*>(obj);
		else
			return nullptr;
	}
private:
	HObject* obj;
	QVector<HObject*> args;
	bool iscoverable = false;
};
extern HLang* HMain;
