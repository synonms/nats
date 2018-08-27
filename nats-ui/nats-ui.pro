QT += qml quick

TEMPLATE = app

CONFIG += c++14

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

INCLUDEPATH += source \
    ../nats-lib/source

HEADERS += \
        source/master-controller.h

SOURCES += \
        source/main.cpp \
        source/master-controller.cpp

RESOURCES += \
    views.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lnats-lib

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
