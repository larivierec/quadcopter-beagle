#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T20:36:54
#
#-------------------------------------------------

QT       += core gui network
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quadcopter-Debugger
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/networkthread.cpp \
    src/tcpserver.cpp

HEADERS  += header/mainwindow.h \
    header/networkthread.h \
    header/tcpserver.h

FORMS    += ui/mainwindow.ui
