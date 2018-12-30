#pragma once
#include <memory>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
namespace HLang {
	class HObject;
}
typedef HLang::HObject* HPointer;
typedef std::vector<HPointer> HArgs;
#define HLANG_NAMESPACE_START namespace HLang {
#define HLANG_NAMESPACE_END }
#define HLANG_OBJECT(__class__)\
public:\
	##__class__(HArgs args);\
	static HPointer __new__(HArgs args){\
		return (new __class__(args))->__init__();\
	}\
	HPointer __do__(std::string function,HArgs args) \
	{\
		return (this->*__##__class__##FunctionSAddress__.at(function))(args); \
	}\
std::string __type__(){\
return std::string(#__class__);\
}\
std::vector<std::string>__list__() {\
std::vector<std::string> v;\
for (std::map<std::string, HPointer(__class__::*)(HArgs)>::iterator it = __##__class__##FunctionSAddress__.begin(); it != __##__class__##FunctionSAddress__.end(); ++it)\
v.push_back(it->first); \
return v;\
}\
protected:\
	std::map<std::string, HPointer(__class__::*)(HArgs)> __##__class__##FunctionSAddress__;
#define HLANG_INIT_START HPointer __init__(){
#define HLANG_INIT_END return this;}
#define HLANG_IMPORT_FUNCTION(__class__,__name__,__function_address__)__##__class__##FunctionSAddress__.insert(std::pair<std::string, HPointer(__class__::*)(HArgs)>(std::string(#__name__),__function_address__))
#define HLANG_INHERITS(__this__,__from__) {\
std::vector<std::string> list = __from__::__list__();\
for (int i = 0; i < (int)list.size(); i++)\
	HLANG_IMPORT_FUNCTION(__this__, list[i], __##__from__##FunctionSAddress__[list[i]])\
}
#define HLANG_CHECKARGS(__need_numbers__,__calut_oper__)\
if (args.size() __calut_oper__ __need_numbers__)\
throw HLang::HError(HLang::HError::ErrorLevel::RT_ERROR,"Args too few or much:[Yours."+std::to_string(args.size())+"][need."+std::to_string(__need_numbers__)+"]");
#define HLANG_IFARGS(__need_numbers__,__calut_oper__)\
if (args.size() __calut_oper__ __need_numbers__)
#define HLANG_CHECKARGTYPE(__which__,__kind__)\
if (args[__which__]->__type__() != #__kind__)\
throw HLang::HError(HLang::HError::ErrorLevel::RT_ERROR,"ArgsType Incorrect [Arg:"#__which__".Type:"+args[__which__]->__type__()+"][TargetType:"#__kind__"]");
#define HLANG_IFARGTYPE(__which__,__kind__) \
if (args[__which__]->__type__() == #__kind__)
#define HLANG_ELSE else

HLANG_NAMESPACE_START
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual  std::vector<std::string>__list__() = 0;
	virtual  HPointer __do__(std::string function, HArgs args) = 0;
	virtual  std::string __type__() = 0;
	virtual  HPointer __init__() = 0;
	template<typename _Target>
	_Target* to()
	{
		return dynamic_cast<_Target*>(this);
	}
};
class HError {
public:
	enum ErrorLevel
	{
		NONE,
		RT_NOTICE,
		RT_WARNING,
		RT_ERROR
	};
	HError(HError::ErrorLevel _elevel = NONE, std::string  _why = "", HPointer _ret = nullptr) {
		this->elevel = _elevel;
		this->why = _why;
		this->ret = _ret;
	};
	HError::ErrorLevel getELevel() const {
		return elevel;
	}
	std::string getWhy() const {
		return why;
	}
	HPointer getObject() const {
		return ret;
	}
private:
	ErrorLevel elevel = NONE;
	HPointer ret = nullptr;
	std::string why = "";
};
HLANG_NAMESPACE_END