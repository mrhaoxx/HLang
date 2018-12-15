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
#include <QSharedPointer>
#define UserColor ((*iscolorful)?std::string("\033[32m").c_str():std::string("").c_str())
#define SystemColor ((*iscolorful)?std::string("\033[34m").c_str():std::string("").c_str())
#define NOCOLOR ((*iscolorful)?std::string("\033[0m").c_str():std::string("").c_str())
#define YELLOWCOLOR ((*iscolorful)?std::string("\033[33;1m").c_str():std::string("").c_str())
#define WARNINGCOLOR ((*iscolorful)?std::string("\033[43;37m").c_str():std::string("").c_str())
#define REDCOLOR ((*iscolorful)?std::string("\033[31;1m").c_str():std::string("").c_str())
#define BWCOLOR ((*iscolorful)?std::string("\033[40;37m").c_str():std::string("").c_str())
#define SKYBLUECOLOR ((*iscolorful)?std::string("\033[36m").c_str():std::string("").c_str())
#define ColorClear ((*iscolorful)?std::string("\033[0m").c_str():std::string("").c_str())
#define BULECOLOR ((*iscolorful)?std::string("\033[32;1m").c_str():std::string("").c_str())
#define PURPLECOLOR ((*iscolorful)?std::string("\033[35m").c_str():std::string("").c_str())
#define WPURPLECOLOR ((*iscolorful)?std::string("\033[45;37m").c_str():std::string("").c_str())
#define HWHITECOLOR ((*iscolorful)?std::string("\033[37;1m").c_str():std::string("").c_str())
extern bool *isdebug;
extern bool *iscolorful;
extern bool *moremsg;
extern QString *indent;
#define IndentAdd indent->append("        ");
#define IndentRem indent->chop(8);
#define RT_DEBUG if(*isdebug)qDebug() << indent->toStdString().c_str() <<UserColor << "[User]" << ColorClear
#define IS_DEBUG if(*isdebug)qDebug() << indent->toStdString().c_str() << SystemColor <<"[System]" << ColorClear
#ifdef WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? QString(strrchr(__FILE__, '\\') + 1).split(".")[0].toStdString().c_str() : QString(__FILE__).split(".")[0].toStdString().c_str())
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? QString(strrchr(__FILE__, '\\') + 1).split(".")[0].toStdString().c_str() :QString(__FILE__).split(".")[0].toStdString().c_str())
#endif

#define MDebug(msg) if(*isdebug&&*moremsg)if(QString(msg).contains("D"))IndentRem else IndentAdd;if(*isdebug&&*moremsg)qDebug()<< indent->toStdString().c_str() <<"["<< (QString(YELLOWCOLOR) + QString(__FILENAME__) + QString(ColorClear)).toStdString().c_str() << "]" << HWHITECOLOR << msg << ColorClear;

#define needQWeight "Only Accept QGuiClass"
#define WhyBuiltinNewFailed "Class Not Find"
#define	WhyBuiltinMsgFailed "Class not Support"
#define WhyFunctionLoadFileFailed "File not find or can't read"
#define WhyIfExecFailed "Which or True or False Result not setup"
#define WhyHWindowAddWeightFailed needQWeight
#define WhyTcpSocketConnectWarring "[Warring]ConnectedSlotNotHandled"
#define WhyConnectSlotError "SIGNAL NOT FIND"
#define HArgs QVector<QSharedPointer<HObject>>
#define H_OBJECT(_name) \
protected: \
QMap<QString,QSharedPointer<HObject>(_name::*)(HArgs args)> memberfuncs##_name; \
public: QSharedPointer<HObject> exec(QString __name,HArgs args){ \
IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << PURPLECOLOR <<"["#_name"]" << ColorClear << " Calling [" << WPURPLECOLOR << __name.toStdString().c_str() << ColorClear <<"]"; \
if (memberfuncs##_name.contains(__name))\
return (this->*memberfuncs##_name[__name])(args); \
throw HError(HError::ELEVEL::RT_ERROR, "FunctionNotFound"); \
}
#define DefineMemberFunction(_class,__name,__function_address) memberfuncs##_class.insert(__name,__function_address)
#define IsGuiClass 	this->QGuiClassHandle = (QWidget*)this;
#define CheckArgs(__needvalues) 	if (args.size() < __needvalues) throw HError(HError::ELEVEL::RT_ERROR,"Args too few or much:[Yours."+QString::number(args.size())+"][need."+QString::number(__needvalues)+"]");
#define CheckArgsType(__which,__kind) if (HObjectHelper(args[__which]).to<__kind>()==nullptr)throw HError(HError::ELEVEL::RT_ERROR,"ArgsType Incorrect [Arg:"#__which"][TargetType:"#__kind"]");
#define InheritFrom(_class,_this) for (int i = 0; i < memberfuncs##_class.keys().length();i++)if (!memberfuncs##_this.contains(memberfuncs##_class.keys()[i]))DefineMemberFunction(_this,memberfuncs##_class.keys()[i],memberfuncs##_class.values()[i])
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual QSharedPointer<HObject> exec(QString __name, HArgs args) = 0;
	QWidget* QGuiClassHandle = nullptr;
};

class HObjectHelper {
public:
	HObjectHelper(QSharedPointer<HObject> obj)
	{
		this->obj = obj;
	}
	template<typename _Target>
	QSharedPointer<_Target> to()
	{
		return obj.dynamicCast<_Target>();
	}
private:
	QSharedPointer<HObject> obj;
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
	HError(HError::ELEVEL Elevel = NONE, QString Why = "", QSharedPointer<HObject> _ret = nullptr) {
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
	QSharedPointer<HObject> getObject() const {
		return ret;
	}
private:
	ELEVEL elevel = NONE;
	QSharedPointer<HObject> ret = nullptr;
	QString why = "";
};
