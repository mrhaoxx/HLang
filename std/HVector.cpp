#include "HVector.h"
#include "HString.h"
#include "HVoid.h"

void HLang::HVector::insert(HPointer d, int w)
{
	Node *t = head;
	Node *l = head;
	for (int i = 0; i <= w; i++)
		if (i != w)
			if (t->next != nullptr) {
				l = t;
				t = t->next;
			}
			else
				if (i != -1)
					return;
				else
				{
					Node* n = new Node;
					n->data = d;
					t->next = n;
				}
		else
		{
			Node* n = new Node;
			n->data = d;
			l->next = n;
			n->next = t;
		}
}

HLang::HVector::HVector(std::string type)
{
	this->type = type;
}

HPointer HLang::HVector::at(int i)
{
	Node *tmp = head;
	for (int t = 0; t <= i; t++)
		if (t != i)
			if (tmp->next != nullptr)
				tmp = tmp->next;
			else
				return nullptr;
		else
			return tmp->data;
	return nullptr;
}

HPointer HLang::HVector::at(HArgs args)
{
	return this->at(args[0]->to<HInt>()->value());
}

void HLang::HVector::removeAt(int i)
{
	Node *tmp = head;
	Node *l = head;
	for (int t = 0; t <= i; t++)
		if (t != i)
			if (tmp->next != nullptr) {
				l = tmp;
				tmp = tmp->next;
			}
			else
				return;
		else
		{
			l->next = tmp->next;
			delete tmp;
		}
}

HPointer HLang::HVector::removeAt(HArgs args)
{
	this->removeAt(args[0]->to<HInt>()->value());
	return HPointer(new HVoid);
}

int HLang::HVector::length()
{
	Node* t = head;
	int l = 0;
	while (t->issaved)
	{
		l++;
		t = t->next;
		if (t == nullptr)
			break;
	}
	return l;
}

HPointer HLang::HVector::length(HArgs args)
{
	return HPointer(HInt::__new__(HArgs())->to<HInt>()->setvalue(this->length()));
}

void HLang::HVector::clear()
{
	while (length() != 0)
		removeAt(length());
}

HPointer HLang::HVector::clear(HArgs args)
{
	this->clear();
	return HPointer(new HVoid);
}

HPointer HLang::HVector::insert_int_data(HArgs args)
{
	this->insert(args[1], args[0]->to<HInt>()->value());
	return HPointer(new HVoid);
}

HPointer HLang::HVector::insert_data(HArgs args)
{
	this->insert(args[0], -1);
	return HPointer(new HVoid);
}

HPointer HLang::HVector::init_string(HArgs args)
{
	this->type = args[0]->to<HString>()->toStdString();
	return HPointer();
}

HLang::HVector::~HVector()
{
	this->clear();
}