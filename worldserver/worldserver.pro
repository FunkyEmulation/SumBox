#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:56
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = worldserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    worldserver.cpp \
    game/server/worldsession.cpp \
    ../shared/configuration/configuration.cpp \
    ../shared/configuration/configmgr.cpp \
    ../shared/databases/mysqlconnection.cpp \
    ../shared/databases/database.cpp \
    ../shared/databases/authdatabase.cpp \
    ../shared/logs/log.cpp \
    ../shared/opcodes/opcodes.cpp \
    ../shared/packets/worldpacket.cpp \
    ../shared/databases/worlddatabase.cpp \
    ../shared/databases/chardatabase.cpp \
    game/chat/chat.cpp

HEADERS += \
    worldserver.h \
    game/server/worldsession.h \
    ../shared/define.h \
    ../shared/configuration/configuration.h \
    ../shared/configuration/configmgr.h \
    ../shared/databases/mysqlconnection.h \
    ../shared/databases/database.h \
    ../shared/databases/authdatabase.h \
    ../shared/logs/log.h \
    ../shared/opcodes/opcodes.h \
    ../shared/packets/worldpacket.h \
    ../shared/packets/worldbuffer.h \
    ../shared/utils/util.h \
    ../shared/databases/worlddatabase.h \
    ../shared/databases/chardatabase.h \
    game/chat/commandline.h \
    game/chat/chat.h
