#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QStringList>
#include <functional>
#include <QWidget>
typedef QVariant HOBJECTS;
#define HClassMap QMap<QString, HObject*>
#define HMemberFunctionMap_def(_class) QMap<QString,HObject*(##_class::*)(HObject*[])>
#define H_OBJECT(_name) \
private: HMemberFunctionMap_def(_name) memberfuncs; \
public: HObject* exec(QString __name, HObject* args[]) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(self, args); \
return new HObject; \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (HLangHelper(args).length() < ##__needvalues) return new HBool(false);
#define H_MemberFunction_def(__name,__class) HObject* __class::##__name(HObject* args[])
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HObject* args[]) {
		qDebug() << "Warring: HObject exec called";
		return new HObject;
	};
	QWidget* QGuiClassHandle = nullptr;
};

struct HCommand {
	QString *_class = nullptr;
	QString *_func = nullptr;
	QString *_self = nullptr;
	QStringList *_args = nullptr;
	QString *_backvalue_name = nullptr;
};
