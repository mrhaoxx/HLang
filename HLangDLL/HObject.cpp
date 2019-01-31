#include "HObject.h"

bool HLang::memorystack::Save(std::string name, HObject* ptr) { if (data.count(name) != 0)return false; this->data.insert(std::make_pair(name, ptr)); return true; }
HLang::HObject* HLang::memorystack::Read(std::string name) { return data.at(name); }
void HLang::memorystack::Delete(std::string name) { data.erase(name); }