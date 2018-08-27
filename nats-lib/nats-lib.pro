QT += network
QT -= gui

TARGET = nats-lib
TEMPLATE = lib

CONFIG += c++14

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
    source/networking/qtsocket.cpp \
    source/client.cpp \
    source/messaging/event-broker.cpp \
    source/messaging/events/connect-event.cpp \
    source/messaging/events/info-event.cpp \
    source/messaging/event-deserialiser.cpp \
    source/messaging/event-serialiser.cpp \
    source/messaging/handlers/info-event-handler.cpp \
    source/logging/console-logger.cpp

HEADERS += \
    source/networking/isocket.h \
    source/nats-lib_global.h \
    source/natsclient.h \
    source/networking/qtsocket.h \
    source/json/ijsonobject.h \
    source/json/qtjsonobject.h \
    source/json/ijsonobjectfactory.h \
    source/json/qtjsonobjectfactory.h \
    source/client.h \
    source/messaging/events/event.h \
    source/messaging/handlers/i-event-handler.h \
    source/messaging/events/event-type.h \
    source/messaging/i-event-broker.h \
    source/messaging/event-broker.h \
    source/messaging/handlers/info-event-handler.h \
    source/messaging/i-event-serialiser.h \
    source/messaging/event-serialiser.h \
    source/messaging/events/connect-event.h \
    source/messaging/events/info-event.h \
    source/messaging/i-event-deserialiser.h \
    source/messaging/event-deserialiser.h \
    source/logging/i-logger.h \
    source/logging/log-level.h \
    source/logging/console-logger.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
