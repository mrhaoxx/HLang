#include <vector>
#include <string>
#include <map>
#define HLANG_EXPORT __declspec(dllexport)
namespace HLang {
	class HLANG_EXPORT HObject {
	public:
		HObject() {}
		virtual ~HObject() {}
		virtual std::string Type(void) = 0;
	};
	class HLANG_EXPORT memorystack {
	public:
		bool Save(std::string name, HObject* ptr);
		HObject* Read(std::string name);
		void Delete(std::string name);
	private:
		std::map<std::string, HObject*> data;
	};
}