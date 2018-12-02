#pragma once
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QStringList>
#include <exception>
#include <typeinfo>
#include <functional>
#include <QWidget>
#include <QVector>
#define ColourfulDebug
#ifdef ColourfulDebug
#define UserColor "\033[32m"
#define SystemColor "\033[34m"
#define NONECOLOR "\033[0m"
#define NOTICECOLOR "\033[33;1m"
#define WARNINGCOLOR "\033[43;37m"
#define ERRORCOLOR "\033[31;1m"
#define WHYCOLOR "\033[40;37m"
#define CDCOLOR "\033[36m"
#define ColorClean "\033[0m"
#define DONECOLOR "\033[32;1m"
#define CLASSCOLOR "\033[35m"
#define FUNCTIONCOLOR "\033[45;37m"
#define ADDRESSCOLOR "\033[37;1m"
#else
#define UserColor ""
#define SystemColor ""
#define NONECOLOR ""
#define NOTICECOLOR ""
#define WARNINGCOLOR ""
#define ERRORCOLOR ""
#define ColorClean ""
#define CDCOLOR ""
#define WHYCOLOR ""
#define DONECOLOR ""
#define CLASSCOLOR ""
#define FUNCTIONCOLOR ""
#define ADDRESSCOLOR ""
#endif

#define RT_DEBUG qDebug() << UserColor << "[User]" << ColorClean
#define IS_DEBUG qDebug() << SystemColor <<"[System]" << ColorClean

#define needQWeight "Only Accept QGuiClass"
#define WhyBuiltinNewFailed "Class Not Find"
#define	WhyBuiltinMsgFailed "Class not Support"
#define WhyFunctionLoadFileFailed "File not find or can't read"
#define WhyIfExecFailed "Which or True or False Result not setup"
#define WhyHWindowAddWeightFailed needQWeight
#define WhyTcpSocketConnectWarring "[Warring]ConnectedSlotNotHandled"
#define WhyConnectSlotError "SIGNAL NOT FIND"
#define HArgs QVector<HObject*>
#define H_OBJECT(_name) \
private: \
QMap<QString,HObject*(_name::*)(HArgs args)> memberfuncs; \
public: HObject* exec(QString __name,HArgs args){ \
IS_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << CLASSCOLOR <<"["#_name"]" << ColorClean << " Calling [" << FUNCTIONCOLOR << __name.toStdString().c_str() << ColorClean <<"]"; \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(args); \
throw HError(HError::ELEVEL::RT_ERROR, "FunctionNotFound"); \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() < __needvalues) throw HError(HError::ELEVEL::RT_ERROR,"Args too few or much:[Yours."+QString::number(args.size())+"][need."#__needvalues+"]");
#define CheckArgsType(__which,__kind) if (HObjectHelper(args[__which]).to<__kind>()==nullptr)throw HError(HError::ELEVEL::RT_ERROR,"ArgsType Incorrect [Arg:"#__which"][TargetType:"#__kind"]");
class HError;
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HArgs args) = 0;
	QWidget* QGuiClassHandle = nullptr;
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
class HError {
public:
	enum ELEVEL
	{
		NONE,
		RT_NOTICE,
		RT_WARNING,
		RT_ERROR
	};
	HError(HError::ELEVEL Elevel = NONE, QString Why = "", HObject* _ret = nullptr) {
		this->elevel = Elevel;
		this->why = Why;
		this->ret = _ret;
	};
	HError::ELEVEL getELevel() const {
		return elevel;
	}
	QString getWhy() const {
		return why;
	}
	HObject* getObject() const {
		return ret;
	}
private:
	ELEVEL elevel = NONE;
	HObject* ret = nullptr;
	QString why = "";
};