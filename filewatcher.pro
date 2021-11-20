QT += core gui widgets

CONFIG += c++11 console
CONFIG -= console

SOURCES += \
        abstractdirectorystrategy.cpp \
        directorystatsmainwindow.cpp \
        filestatmodel.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

DESTDIR = $$PWD/../out

HEADERS += \
    abstractdirectorystrategy.h \
    directorystatsmainwindow.h \
    filestatmodel.h \
    groupfilestrategy.h \
    listfilestrategy.h

FORMS += \
    directorystatsmainwindow.ui
