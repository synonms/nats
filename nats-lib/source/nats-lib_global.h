#ifndef NATSLIB_GLOBAL_H
#define NATSLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NATSLIB_LIBRARY)
#  define NATSLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NATSLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
