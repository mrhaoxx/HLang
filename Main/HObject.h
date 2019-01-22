#ifndef HOBJECT_H
#define HOBJECT_H
#include <map>
#include <string>
#include <utility>
#include <vector>
#define HLANG_EXPORT __declspec(dllexport)  // Export To Static Lib
#define HLANG_OBJECT(__class__)             /*HLang Object Header*/    \
                                                                       \
 public:                                                               \
  HLANG_EXPORT static HLang::HPointer New(HArgs args) {                \
    return (new __class__)->Construct(args);                           \
  }                                                                    \
  HPointer Do(std::string function, HArgs args) {                      \
    std::vector<std::string> argclasses;                               \
    for (int i = 0; i < args.size(); i++)                              \
      argclasses.push_back(args[i]->__type__());                       \
    if (__##__class__##FunctionSAddress__.count(                       \
            std::make_pair(function, argclasses)) != 0)                \
      return (this->*__##__class__##FunctionSAddress__.at(             \
                         std::make_pair(function, argclasses)))(args); \
    return nullptr;                                                    \
  }                                                                    \
                                                                       \
 protected:                                                            \
  std::map<std::pair<std::string, std::vector<std::string>>,           \
           HPointer (__class__::*)(HArgs)>                             \
      __##__class__##FunctionSAddress__;

#define HLANG_INIT_HEAD HPointer Construct(HArgs args)
namespace HLang {
class HObject;
class HPointer;
typedef std::vector<HPointer*> HArgs;
class HObject {
  virtual HPointer Construct(HArgs args) = 0;
  virtual HPointer Destruct() = 0;
  virtual HPointer Do(std::string function, HArgs args) = 0;
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