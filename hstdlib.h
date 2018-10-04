#ifndef HSTDLIB_H
#define HSTDLIB_H
#include "hobject.h"
#define Separator " "

class HStdLib : public HObject
{
public:
    HStdLib(){
        this->map.insert("print", std::function<HArgs(HArgs)>(print));
    }
    static HArgs print(HArgs);

};

#endif // HSTDLIB_H
