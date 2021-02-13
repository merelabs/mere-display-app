#include(../mere-display-lib/mere-display-lib.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menshen
TEMPLATE = app

DEFINES += APP_CODE=\\\"display\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/app.cpp \
    src/client.cpp \
    src/config.cpp \
    src/main.cpp \
    src/screen.cpp \
    src/simplescreen.cpp \
    src/win.cpp


HEADERS += \
    src/app.h \
    src/client.h \
    src/config.h \
    src/screen.h \
    src/simplescreen.h \
    src/win.h

RESOURCES += \
    res/display.qrc

INCLUDEPATH += /usr/local/include

LIBS += -lmere-display -lmere-rpc -lmere-widgets -lmere-utils
#LIBS += -lmere-display -lmere-display-client

#
# Install
#
unix{
    target.path = /usr/local/bin
    INSTALLS += target
}

DISTFILES += \
    res/display.qss

