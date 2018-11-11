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
#define HMemberFunctionMap_def(_class) QMap<QString,HObject*(##_class::*)(HOBJECTS,HOBJECTS)>
#define H_OBJECT(_name) \
private: HMemberFunctionMap_def(_name) memberfuncs; \
public: HObject* exec(QString __name, HOBJECTS self, HOBJECTS args) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(self, args); \
return new HObject; \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (__arglist.toStringList().length() < ##__needvalues)return new HBool(false);
#define SetupArgs QStringList args=__arglist.toStringList();
#define GetArg(_num) args.at((_num))

#define H_MemberFunction_def(__name,__class) HObject* __class::##__name(HOBJECTS __self, HOBJECTS __arglist)
#define HObjTo(_object,_target) (dynamic_cast<_target>(_object))
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HOBJECTS self, HOBJECTS args) {
		qDebug() << "Warring: HObject exec called";
		return new HObject;
	};
	QWidget* QGuiClassHandle = nullptr;
};

struct HCommand {
	QString _class;
	QString _func;
	QString _self;
	QStringList _args;
	QString _backvalue_name;
};
