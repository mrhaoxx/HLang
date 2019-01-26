#ifndef MEMORY_STACK_H
#define MEMORY_STACK_H
#include <map>
#include <string>
#include "HObject.h"
class memstack {
public:
	struct data {
		data(std::string t, HLang::HPointer p) : ptr(p), type(t) {}
		HLang::HPointer ptr;
		std::string type;
		operator std::string() { return type; }
		operator HLang::HPointer() { return ptr; }
	};
	bool save(std::string name, std::string type, HLang::HPointer ptr);
	data get(std::string name);
	void remove(std::string name);

private:
	std::map<std::string, data> stack;
};
#endif
