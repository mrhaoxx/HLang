#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <functional>
#include <QWidget>
#define needHString "Only Accept HString"
#define needHBool "Only Accept HBool"
#define needHFunction "Only Accept HFunction"
#define needQWeight "Only Accept QGuiClass"
#define WhyBuiltinNewFailed "Class Not Find"
#define WhyBuiltinDeleteFailed needHString
#define WhyBuiltinSystemFailed needHString
#define	WhyBuiltinMsgFailed "Class not Support"
#define WhyFunctionAddFailed needHString
#define WhyFunctionLoadFileFailed "File not find or can't read"
#define WhyIfSetWhichFailed needHBool
#define WhyIfSetTrueFailed needHFunction
#define WhyIfSetFalseFailed needHFunction
#define WhyIfExecFailed "True or False Result not setup"
#define WhyHPushButtonSetClickedFailed needHFunction
#define WhyHPushButtonSetTextFailed needHString
#define WhyHWindowSetTitleFailed needHString
#define WhyHWindowAddWeightFailed needQWeight
#define WhyFunctionLinkFailed needHString
#define HClassMap QMap<QString, HObject*>
#define HMemberFunctionMap_def(_class) QMap<QString,HObject*(##_class::*)(HArgs args)>
#define HArgs std::vector<HObject*>
#define H_OBJECT(_name) \
private: \
HMemberFunctionMap_def(_name) memberfuncs; \
public: HObject* exec(QString __name,HArgs args) { \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(args); \
return new HRet(nullptr, false, "[Class."#_name"][Function."+__name+"]Not Find"); \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() != ##__needvalues) return new HRet(nullptr,false,"Args too few or much:[Yours."+QString::number(args.size())+"][need."#__needvalues+"]");
#define CheckArgsType(__which,__kind) if (HObjectHelper(args[__which]).to<__kind>()==nullptr)return new HRet(nullptr,false,"ArgsType Incorrect [Arg."#__which"][TargetType.:"#__kind"]")
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HArgs args) {
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
class HRet :public HObject
{
public:
	HRet(HObject* ret = nullptr, bool isSuccess = true, QString reason = "")
	{
		this->isSuccess = isSuccess;
		this->ret = ret;
		this->reason = reason;
	}
	HRet(bool isSuccess)
	{
		this->isSuccess = isSuccess;
	}
	bool getSuccess() {
		return isSuccess;
	}
	HObject* getObject() {
		return ret;
	}
	QString getReason() {
		return reason;
	}
private:
	bool isSuccess = false;
	HObject* ret = nullptr;
	QString reason;
};
