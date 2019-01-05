#pragma once
#include "HObject.h"
#include "HInt.h"

HLANG_NAMESPACE_START
class HVector :
	public HLang::HObject
{
	HLANG_OBJECT(HVector);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HVector, insert, HLANG_ARGSPILT(this->type), &HLang::HVector::insert_data);
	HLANG_IMPORT_FUNCTION(HVector, insert, HLANG_ARGSPILT("HInt," + this->type), &HLang::HVector::insert_int_data);
	HLANG_IMPORT_FUNCTION(HVector, at, HLANG_ARGSPILT(""), &HLang::HVector::at);
	HLANG_IMPORT_FUNCTION(HVector, removeAt, HLANG_ARGSPILT("HInt"), &HLang::HVector::removeAt);
	HLANG_IMPORT_FUNCTION(HVector, length, HLANG_ARGSPILT(""), &HLang::HVector::length);
	HLANG_IMPORT_FUNCTION(HVector, clear, HLANG_ARGSPILT(""), &HLang::HVector::clear);
	HLANG_IMPORT_FUNCTION(HVector, init, HLANG_ARGSPILT("HString"), &HLang::HVector::init_string);
	head = new Node;
	HLANG_INIT_END
		struct Node
	{
		Node *next = nullptr;
		HPointer data;
		bool issaved = false;
	}*head = nullptr;
	std::string type = "";
public:
	HVector(std::string type = "");
	HPointer insert_int_data(HArgs args);
	HPointer insert_data(HArgs args);
	HPointer at(HArgs args);
	HPointer removeAt(HArgs args);
	HPointer length(HArgs args);
	HPointer clear(HArgs args);
	HPointer init_string(HArgs args);
protected:
	void insert(HPointer d, int w = -1);
	HPointer at(int i);
	void removeAt(int i);
	void clear();
	int length();
	~HVector();
};
HLANG_NAMESPACE_END
