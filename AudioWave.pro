QT += core
QT += gui
QT += widgets

CONFIG += c++11

TARGET = AudioWave
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    maplaya2.cpp \
    playbacktracker.cpp \
    trackwrapper.cpp \
    staticfunctions.cpp \
    customslider.cpp

win32: LIBS += -L$$PWD/./ -lbass
win32: LIBS += -L$$PWD/./ -lcomdlg32
LIBS += -$$PWD/./-lcomdlg32
#LIBS = -lcomdlg32
LIBS += -L$$PWD/./-lbass
#LIBS += comdlg32.lib

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

#win32:!win32-g++:
PRE_TARGETDEPS += $$PWD/./bass.lib
PRE_TARGETDEPS += $$PWD/./comdlg32.dll
#else:win32-g++: PRE_TARGETDEPS += $$PWD/./libbass.a

FORMS += \
    maplaya2.ui

HEADERS += \
    maplaya2.h \
    playbacktracker.h \
    trackwrapper.h \
    staticfunctions.h \
    customslider.h

RESOURCES += \
    timelinepixmap.qrc
