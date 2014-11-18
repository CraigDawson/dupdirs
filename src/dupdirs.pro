#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T09:41:23
#
#-------------------------------------------------
QMAKE_MAC_SDK = macosx10.9

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dupdirs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        dupdir.cpp \
        quote_iomanip.cpp \
        fts_wrapper.cpp \
        num_comp.cpp

HEADERS  += mainwindow.h \
    ../hashlib2plus/trunk/src/hashlibpp.h \
    dupdir.h \
    log.h \
    smtimer.h \
    cxd_license.h \
    fts_wrapper.h \
    quote_iomanip.h \
    num_comp.h

FORMS    += mainwindow.ui

#unix:macx: LIBS += -L$$PWD/../hashlib2plus/trunk/src/ -lhl++
unix: LIBS += -L$$PWD/../hashlib2plus/trunk/src/ -lhl++

INCLUDEPATH += $$PWD/../hashlib2plus/trunk/src
DEPENDPATH += $$PWD/../hashlib2plus/trunk/src

#unix:macx: PRE_TARGETDEPS += $$PWD/../hashlib2plus/trunk/src/libhl++.a
unix: PRE_TARGETDEPS += $$PWD/../hashlib2plus/trunk/src/libhl++.a

#INCLUDEPATH += ../../../dupdir

CONFIG += c++11

OTHER_FILES += \
    ../README.md
    ../TODO.md
