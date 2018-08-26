QT += network
QT -= gui

TARGET = nats-lib
TEMPLATE = lib

DEFINES += NATSLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

INCLUDEPATH += source

SOURCES += \
    source/networking/qtsocket.cpp

HEADERS += \
    source/networking/isocket.h \
    source/synonats-lib_global.h \
    source/natsclient.h \
    source/networking/qtsocket.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
