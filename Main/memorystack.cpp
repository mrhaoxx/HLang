#include "memorystack.h"
bool memstack::save(std::string type, std::string name, HLang::HPointer ptr) {
	if (stack.count(name) != 0) return false;
	this->stack.insert(std::make_pair(name, data(type, ptr)));
	return true;
}

memstack::data memstack::get(std::string name) { return stack.at(name); }

void memstack::remove(std::string name) { stack.erase(name); }