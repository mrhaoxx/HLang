#ifndef HOBJECT_H
#define HOBJECT_H
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#define HLANG_EXPORT __declspec(dllexport)  // Export To Static Lib
#define HLANG_OBJECT(__class__)             /* HLang Object Header */                                                         \
                                                                                                                              \
 public:                                                                                                                      \
  HLANG_EXPORT static HLang::HPointer New(HArgs args) {                                                                       \
    return (new __class__(args));                                                                                             \
  }                                                                                                                           \
  HPointer Do(std::string function, HArgs args) {                                                                             \
    std::vector<std::string> argclasses;                                                                                      \
    for (int i = 0; i < args.size(); i++)                                                                                     \
      argclasses.push_back(args[i].Get()->Type());                                                                            \
    if (__##__class__##FunctionSAddress__.count(std::make_pair(function, argclasses)) != 0)                                   \
      return (this->*__##__class__##FunctionSAddress__.at(std::make_pair(function, argclasses)))(args);                       \
    return nullptr;                                                                                                           \
  }                                                                                                                           \
  std::string Type() { return std::string(#__class__); }                                                                      \
                                                                                                                              \
protected:                                                                                                                    \
  std::map<std::pair<std::string, std::vector<std::string>>,HPointer (__class__::*)(HArgs)>__##__class__##FunctionSAddress__;

#define HLANG_INIT_HEAD(_class) _class(HArgs args)
#define HLANG_ITFU_HEAD(_class, _upper)/* Head */ \
HLANG_INIT_HEAD(_class) : _upper(args)
#define HLANG_DSTR_HEAD(_class) HPointer ~##_class(HArgs args)

namespace HLang {
	class HObject;
	class HPointer;
	typedef std::vector<HPointer> HArgs;
	typedef std::function<HPointer(HArgs)> HClassRegHandle;
	class HObject {
		// virtual HPointer Construct(HArgs args) = 0;
		// virtual HPointer Destruct() = 0;
	public:
		HObject(HArgs args) {};
		HObject() {};
		virtual HPointer Do(std::string function, HArgs args) = 0;
		virtual std::string Type() = 0;
	};
	class HPointer {
	public:
		HPointer(HObject* ptr = nullptr);
		bool IsNull();
		HObject* Get();
		void Delete();
		HObject* operator->();
		HObject& operator*();
		void setup(HObject* ptr = nullptr, bool isDeleteBefore = true);

	private:
		HObject* data;
	};
}  // namespace HLang
#endif