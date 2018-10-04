#include "hstdlib.h"
#include <QMessageBox>

HArgs HStdLib::print(HArgs args)
{
    QStringList msg=args().split(Separator);
    msg.removeFirst();
    msg.removeFirst();
    QMessageBox::information(nullptr,"",msg.join(Separator));
    return HArgs("ok");
}
