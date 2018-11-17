#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <functional>
#include <QWidget>
#define HClassMap QMap<QString, HObject*>
#define HMemberFunctionMap_def(_class) QMap<QString,HObject*(##_class::*)(std::vector<HObject*> args)>
#define H_OBJECT(_name) \
private: \
HMemberFunctionMap_def(_name) memberfuncs; \
public: HObject* exec(QString __name,std::vector<HObject*> args) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(args); \
return new HObject; \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() < ##__needvalues) return new HBool(false);
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, std::vector<HObject*> args) {
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
class HObjectHelper {
public:
	HObjectHelper(HObject* obj)
	{
		this->obj = obj;
	}
	template<typename _Target>
	_Target* to()
	{
		return dynamic_cast<_Target*>(obj);
	}
private:
	HObject* obj;
};