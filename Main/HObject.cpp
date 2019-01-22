#include "HObject.h"
HLang::HPointer::HPointer(HObject* ptr) { this->data = ptr; }

bool HLang::HPointer::IsNull() {
  if (data == nullptr)
    return true;
  else
    return false;
}

HLang::HObject* HLang::HPointer::Get() { return data; }

void HLang::HPointer::Delete() {
  if (!IsNull()) delete data;
  data = nullptr;
}

HLang::HObject* HLang::HPointer::operator->() { return this->Get(); }

HLang::HObject& HLang::HPointer::operator*() { return *this->Get(); }

void HLang::HPointer::setup(HObject* ptr /*= nullptr*/,
                            bool isDeleteBefore /*= true*/) {
  if (isDeleteBefore) Delete();
  this->data = ptr;
}