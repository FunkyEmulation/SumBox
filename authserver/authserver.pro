#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:24
#
#-------------------------------------------------

QT       += core network xml

QT       -= gui

TARGET = authserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    authserver.cpp \
    authsocket.cpp

HEADERS += \
    ../shared/define.h \
    authserver.h \
    authsocket.h