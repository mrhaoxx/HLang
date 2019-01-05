#include "HString.h"
#include "HByte.h"

std::string HLang::HString::toStdString()
{
	std::string buf;
	for (int i = 0; i < this->length(); ++i)
		buf.push_back(this->at(i)->to<HByte>()->value());
	return buf;
}

HLang::HString* HLang::HString::setvalue(std::string str)
{
	this->clear();
	for (int i = 0; i < str.length(); i++)
		this->insert(HLang::HByte::__new__(HArgs())->to<HByte>()->setvalue(str.at(i)));
	return this;
}

HLang::HString::HString(std::string str /*= ""*/) : HVector("HByte")
{
	this->setvalue(str);
}