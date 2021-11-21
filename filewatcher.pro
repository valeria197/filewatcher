QT += core gui widgets charts

CONFIG += c++11 console
CONFIG -= console

SOURCES += \
        abstractdirectorystrategy.cpp \
        abstractstatholder.cpp \
        chartupdater.cpp \
        directorystatsmainwindow.cpp \
        filestatmodel.cpp \
        groupfilestrategy.cpp \
        listfilestrategy.cpp \
        main.cpp

DESTDIR = $$PWD/../out

HEADERS += \
    abstractdirectorystrategy.h \
    abstractstatholder.h \
    chartupdater.h \
    directorystatsmainwindow.h \
    filestatmodel.h \
    groupfilestrategy.h \
    listfilestrategy.h

FORMS += \
    directorystatsmainwindow.ui
