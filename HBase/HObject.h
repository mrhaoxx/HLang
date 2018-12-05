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
#define UserColor(iscolorful)?std::string("\033[32m"):std::string("")
#define SystemColor (iscolorful)?std::string("\033[34m"):std::string("")
#define NONECOLOR (iscolorful)?std::string("\033[0m"):std::string("")
#define NOTICECOLOR (iscolorful)?std::string("\033[33;1m"):std::string("")
#define WARNINGCOLOR (iscolorful)?std::string("\033[43;37m"):std::string("")
#define ERRORCOLOR (iscolorful)?std::string("\033[31;1m"):std::string("")
#define WHYCOLOR (iscolorful)?std::string("\033[40;37m"):std::string("")
#define CDCOLOR (iscolorful)?std::string("\033[36m"):std::string("")
#define ColorClean (iscolorful)?std::string("\033[0m"):std::string("")
#define DONECOLOR (iscolorful)?std::string("\033[32;1m"):std::string("")
#define CLASSCOLOR (iscolorful)?std::string("\033[35m"):std::string("")
#define FUNCTIONCOLOR (iscolorful)?std::string("\033[45;37m"):std::string("")
#define ADDRESSCOLOR (iscolorful)?std::string("\033[37;1m"):("")
extern bool isdebug;
extern bool iscolorful;
#define RT_DEBUG if(isdebug)qDebug() << UserColor << "[User]" << ColorClean
#define IS_DEBUG if(isdebug)qDebug() << SystemColor <<"[System]" << ColorClean

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
