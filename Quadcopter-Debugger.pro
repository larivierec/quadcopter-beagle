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


SOURCES += main.cpp\
        mainwindow.cpp \
    networkthread.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    networkthread.h \
    tcpserver.h

FORMS    += mainwindow.ui
