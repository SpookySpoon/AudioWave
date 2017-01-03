QT += core
QT += gui
QT += widgets

CONFIG += c++11

TARGET = AudioWave
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    playbacktracker.cpp \
    trackwrapper.cpp \
    staticfunctions.cpp \
    customslider.cpp \
    contextmenu.cpp \
    playerui.cpp \
    playlist.cpp

win32: LIBS += -L$$PWD/./ -lbass
LIBS += -L$$PWD/./-lbass

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

#win32:!win32-g++:
PRE_TARGETDEPS += $$PWD/./bass.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/./libbass.a

FORMS += \
    plauerui.ui

HEADERS += \
    playbacktracker.h \
    trackwrapper.h \
    staticfunctions.h \
    customslider.h \
    contextmenu.h \
    playerui.h \
    playlist.h

RESOURCES += \
    timelinepixmap.qrc
