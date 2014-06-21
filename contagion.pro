#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T07:32:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contagion
TEMPLATE = app
QMAKE_CXXFLAGS  = -std=c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    humanitem.cpp

HEADERS  += mainwindow.h \
    game.h \
    humanitem.h \
    defs.h

OTHER_FILES += \
    Tasks.txt


