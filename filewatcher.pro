QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        abstractdirectorystrategy.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

DESTDIR = $$PWD/../out

HEADERS += \
    abstractdirectorystrategy.h \
    groupfilestrategy.h \
    listfilestrategy.h
