#ifndef QT_GLOBAL_H
#define QT_GLOBAL_H
#include "HObject.h"
#include <QtCore/qglobal.h>
#include "QApplication"

#if defined(QT_LIBRARY)
#  define QTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTSHARED_EXPORT Q_DECL_IMPORT
#endif

QApplication *app = nullptr;

#endif // QT_GLOBAL_H
