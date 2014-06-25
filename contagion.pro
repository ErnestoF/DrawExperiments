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

SOURCES += game.cpp \
    humanitem.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp \
    gamestate.cpp \
    randomclient.cpp

HEADERS  += defs.h \
    game.h \
    humanitem.h \
    mainwindow.h \
    server.h \
    gamestate.h \
    abstractclient.h \
    randomclient.h


OTHER_FILES += \
    Tasks.txt


