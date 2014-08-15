#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T07:32:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contagion
TEMPLATE = app
QMAKE_CXX = clang
QMAKE_CXXFLAGS  = -std=c++11

SOURCES += \
    gamesession.cpp \
    humanitem.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp \
    gamestate.cpp \
    randomclient.cpp \
    guiclient.cpp \
    guessresponse.cpp \
    defs.cpp

HEADERS  += \
    defs.h \
    gamesession.h \
    humanitem.h \
    mainwindow.h \
    server.h \
    gamestate.h \
    abstractclient.h \
    randomclient.h \
    guiclient.h \
    guessresponse.h


OTHER_FILES += \
    Tasks.txt


