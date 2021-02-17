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
    src/client.cpp \
    src/displayapp.cpp \
    src/displaywin.cpp \
    src/main.cpp \
    src/screen.cpp \
    src/simplescreen.cpp


HEADERS += \
    src/client.h \
    src/displayapp.h \
    src/displaywin.h \
    src/screen.h \
    src/simplescreen.h

RESOURCES += \
    res/display.qrc

DISTFILES += \
    res/display.qss


INCLUDEPATH += /usr/local/include

LIBS += -lmere-display -lmere-rpc -lmere-widgets -lmere-utils
#LIBS += -lmere-display -lmere-display-client



#
# Generate TS file
#
LANGUAGES = en bn
defineReplace(prependAll) {
    for(a, $$1): result += $$2$${a}$$3
    return($$result)
}
TRANSLATIONS = $$prependAll(LANGUAGES, i18n/display_, .ts)
qtPrepareTool(LUPDATE, lupdate)
command = $$LUPDATE mere-display-app.pro
system($$command)|error("Failed to run: $$command")

#
# Generate QM file from TS file, and
# Copy to the resource bundle
#
TRANSLATIONS_FILES =
qtPrepareTool(LRELEASE, lrelease)
for(tsfile, TRANSLATIONS) {
    qmfile = $$tsfile
    qmfile ~= s,.ts,.qm

    command = $$LRELEASE -removeidentical $$tsfile -qm $$qmfile
    system($$command)|error("Failed to run: $$command")
    TRANSLATIONS_FILES += $$qmfile
}


#
# Install
#
unix
{
    target.path = /usr/local/bin
    INSTALLS += target

    i18n.path = /usr/local/share/mere/display/i18n
    i18n.files = $$TRANSLATIONS_FILES
    INSTALLS += i18n
}
