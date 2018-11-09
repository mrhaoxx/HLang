#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include <functional>
#include <QWidget>
typedef QVariant HOBJECTS;
typedef QString HString;
#define HClassMap QMap<HString, HObject*>
#define QGuiClassMap QMap<HString, QWidget*>
#define HVarrMap QMap<HString, HOBJECTS*>
#define HMemberFunctionMap_def(_class) QMap<HString,HOBJECTS(##_class::*)(HOBJECTS,HOBJECTS)>
#define H_OBJECT(_name) \
private: HMemberFunctionMap_def(_name) memberfuncs; \
public: HOBJECTS exec(HString __name, HOBJECTS self, HOBJECTS args) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(self, args); \
return HOBJECTS(); \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define CheckArgs(__needvalues) 	if (__arglist.toStringList().length() < ##__needvalues)return HOBJECTS(false);
#define H_MemberFunction_def(__name,__class) HOBJECTS __class::##__name(HOBJECTS __self, HOBJECTS __arglist)
#define IsVarrsToStr(str) (HMain->accessvarrs(str)!=nullptr)?(HMain->accessvarrs(str)->toString()):(str)
#define IsVarrsToObj(str) (HMain->accessvarrs(str)!=nullptr)?*(HMain->accessvarrs(str)):HOBJECTS(str)
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HOBJECTS exec(HString __name, HOBJECTS self, HOBJECTS args) {
		qDebug() << "Warring: HObject exce called";
		return HOBJECTS();
	};
};

struct HCommand {
	HString _class;
	HString _func;
	HString _self;
	QStringList _args;
	HString _backvalue_name;
};