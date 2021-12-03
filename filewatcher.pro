QT += core gui widgets charts

CONFIG += c++11 console
CONFIG -= console

SOURCES += \
        abstractdirectorystrategy.cpp \
        chartupdater.cpp \
        filestatmodel.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp \
        statsmainwindow.cpp

DESTDIR = $$PWD/../out

HEADERS += \
    abstractdirectorystrategy.h \
    chartupdater.h \
    filestatmodel.h \
    groupfilestrategy.h \
    listfilestrategy.h \
    statsmainwindow.h

FORMS += \
    statsmainwindow.ui
