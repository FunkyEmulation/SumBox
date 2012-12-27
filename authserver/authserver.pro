#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:24
#
#-------------------------------------------------

QT       += core network xml sql

QT       -= gui

TARGET = authserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    authserver.cpp \
    authsocket.cpp \
    ../shared/opcodes/opcodes.cpp \
    ../worldserver/game/server/worldsession.cpp \
    AuthConfig.cpp \
    Database/Models/AccountModel.cpp \
    Database/DatabaseHandler.cpp \
    Database/Models/ServerModel.cpp \
    Com/ComServer.cpp \
    Com/GameSocket.cpp \
    AuthModel.cpp

HEADERS += \
    ../shared/define.h \
    authserver.h \
    authsocket.h \
    ../shared/utils/util.h \
    ../shared/opcodes/opcodes.h \
    ../shared/packets/worldpacket.h \
    ../shared/packets/worldbuffer.h \
    ../worldserver/game/server/worldsession.h \
    AuthConfig.h \
    Database/Models/AccountModel.h \
    Database/DatabaseHandler.h \
    Database/Models/ServerModel.h \
    Com/ComServer.h \
    Com/GameSocket.h \
    AuthModel.h
