#pragma once
#include <memory>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
extern std::vector<std::string> split(std::string str, std::string pat);
namespace HLang {
	class HObject;
}
typedef HLang::HObject* HPointer;
typedef std::vector<HPointer> HArgs;
#define HLANG_NAMESPACE_START namespace HLang {
#define HLANG_NAMESPACE_END }
#define HLANG_OBJECT(__class__)\
public:\
	static HPointer __new__(HArgs args){\
			return (new __class__)->__init__(args); \
	}\
	HPointer __do__(std::string function, HArgs args) \
	{\
	std::vector<std::string> argclasses; \
	for (int i = 0; i < args.size(); i++)\
		argclasses.push_back(args[i]->__type__()); \
	if (__##__class__##FunctionSAddress__.count(std::make_pair(function, argclasses)) > 0)\
				return (this->*__##__class__##FunctionSAddress__.at(std::make_pair(function,argclasses)))(args); \
		return nullptr;\
	}\
	std::string __type__(){\
		return std::string(#__class__);\
	}\
	std::vector<std::pair<std::string,std::vector<std::string>>>__list__() {\
		std::vector<std::pair<std::string,std::vector<std::string>>> v;\
		for (std::map<std::pair<std::string,std::vector<std::string>>, HPointer(__class__::*)(HArgs)>::iterator it = __##__class__##FunctionSAddress__.begin(); it != __##__class__##FunctionSAddress__.end(); ++it)\
			v.push_back(it->first); \
		return v;\
	}\
protected:\
	std::map<std::pair<std::string,std::vector<std::string>>, HPointer(__class__::*)(HArgs)> __##__class__##FunctionSAddress__;
#define HLANG_INIT_START HPointer __init__(HArgs args){
#define HLANG_INIT_END this->__do__("init",args);return this;}
#define HLANG_IMPORT_FUNCTION(__class__,__name__,__args__,__function_address__)__##__class__##FunctionSAddress__.insert(std::pair<std::pair<std::string,std::vector<std::string>>, HPointer(__class__::*)(HArgs)>(std::make_pair(std::string(#__name__),__args__),__function_address__))
#define HLANG_ARGSPILT(str) split(std::string(str),std::string(","))
#define HLANG_INHERITS(__this__,__from__) {\
std::vector<std::pair<std::string,std::vector<std::string>>> list = __from__::__list__();\
for (int i = 0; i < (int)list.size(); i++)\
	HLANG_IMPORT_FUNCTION(__this__, list[i].first,list[i].second, __##__from__##FunctionSAddress__[list[i]]);\
}
HLANG_NAMESPACE_START
class HObject
{
public:
	HObject() {};
	virtual ~HObject() {};
	virtual  std::vector<std::pair<std::string, std::vector<std::string>>> __list__() = 0;
	virtual  HPointer __do__(std::string function, HArgs args) = 0;
	virtual  std::string __type__() = 0;
	virtual  HPointer __init__(HArgs args) = 0;
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