#ifndef HCLASS_H
#define HCLASS_H
#include "HObject.h"
namespace HLang {
	class HClass : public HObject {
		HLANG_OBJECT(HClass)
	public:
		HClass(HArgs args) {
		}
	private:
	};
}  // namespace HLang

#endif
