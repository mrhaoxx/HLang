#ifndef CLASS_H
#define CLASS_H
#include <tuple>
#include <vector>
#include <functional>
#include <map>
#define INST_HD static Class* __instance__(args) {};
class Class;
typedef std::vector<Class*> args;
class Class
{
public:
	Class(std::string name) : type(name) {};
	virtual std::string __type__(void) { return type; };    
	virtual Class* __init__(args) = 0;							  
	template<typename T>
	inline T* to(void) { //Cover The Pointer to T
		return dynamic_cast<T*>(this);
	}				
private:
	bool is_inited = false;
	std::vector<std::pair<std::string, std::function<Class*(args)>>> init_classes_new_handle;
	std::map<std::string, Class*> pool;
	std::string type;
};
/*
	Class:
		Root of All classes
		has a function __type__ return class name
		//has a function __callable__ return class is callable

*/
#endif														
									   