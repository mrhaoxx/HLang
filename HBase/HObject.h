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

#define RT_DEBUG qDebug() << "[UserCommand]"
#define IS_DEBUG qDebug() << "[System]"

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
IS_DEBUG << ">>" << (void*)this << "<<" << "[Class."#_name"] Calling [Function."<< __name.toStdString().c_str() << "]"; \
if (memberfuncs.contains(__name))\
return (this->*memberfuncs[__name])(args); \
throw HError(HError::ELEVEL::RT_ERROR, "FunctionNotFound"); \
}
#define DefineMemberFunction(__name,__function_address) memberfuncs.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() < __needvalues) throw HError(HError::ELEVEL::RT_ERROR,"Args too few or much:[Yours."+QString::number(args.size())+"][need."#__needvalues+"]");
#define CheckArgsType(__which,__kind) if (HObjectHelper(args[__which]).to<__kind>()==nullptr)throw HError(HError::ELEVEL::RT_ERROR,"ArgsType Incorrect [Arg."#__which"][TargetType.:"#__kind"]");
class HError;
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual HObject* exec(QString __name, HArgs args) = 0;
	QWidget* QGuiClassHandle = nullptr;
};

struct HCommand {
	QString _class;
	QString _func;
	QStringList _args;
	QString _backvalue_name;
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