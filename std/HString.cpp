#include "HString.h"
#include "HByte.h"

HLang::HString::~HString()
{
}
HLang::HString::HString() {
}
std::string HLang::HString::toStdString()
{
	std::string buf;
	for (int i = 0; i < this->length(); ++i)
		buf.push_back(this->at(i)->to<HByte>()->value());
	return buf;
}