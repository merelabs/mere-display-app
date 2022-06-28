#include(../mere-display-lib/mere-display-lib.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = menshen
TEMPLATE = app

DEFINES += APP_CODE=\\\"display\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/main.cpp \
    src/client.cpp \
    src/config.cpp \
    src/screen.cpp \
    src/passer.cpp \
    src/displayapp.cpp \
    src/theme.cpp \
    src/themes/simple/actionview.cpp \
    src/themes/simple/clockview.cpp \
    src/themes/simple/promptscreen.cpp \
    src/themes/simple/sessionview.cpp \
    src/themes/simple/simplescreen.cpp


HEADERS += \
    src/client.h \
    src/config.h \
    src/passer.h \
    src/screen.h \
    src/displayapp.h \
    src/theme.h \
    src/themes/simple/actionview.h \
    src/themes/simple/clockview.h \
    src/themes/simple/promptscreen.h \
    src/themes/simple/sessionview.h \
    src/themes/simple/simplescreen.h

RESOURCES += \
    res/display.qrc

DISTFILES += \
    etc/display.conf
    share/mere-logo.png
    share/freebsd-logo.png

TRANSLATIONS += \
    i18n/display_bn.ts \
    i18n/display_en.ts


INCLUDEPATH += /usr/local/include
LIBS += -lmere-config-lite -lmere-rpc -lmere-widgets -lmere-xdg -lmere-utils

##
## TS file(s)
##
#qtPrepareTool(LUPDATE, lupdate)
#command = $$LUPDATE mere-display.pro
#system($$command)|error("Failed to run: $$command")

#
# Generate QM file(s) from TS file(s)
#
qtPrepareTool(LRELEASE, lrelease)
command = $$LRELEASE -removeidentical i18n/*.ts
system($$command)|error("Failed to run: $$command")

#
# Install
#
unix
{
    target.path = /usr/local/bin
    INSTALLS += target

    config.path = /usr/local/etc/mere/
    config.files += etc/display.conf
    INSTALLS += config

    i18n.path = /usr/local/share/mere/display/i18n
    i18n.files = i18n/*.qm
    INSTALLS += i18n

    share.path = /usr/local/share/mere/display/
    share.files += share/mere-logo.png share/freebsd-logo.png
    INSTALLS += share

}
