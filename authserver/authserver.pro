#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T16:39:24
#
#-------------------------------------------------

QT       += core network sql
QT       -= gui

TARGET = authserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += . ../shared ../worldserver
DEPENDPATH += . ../shared ../worldserver

SOURCES += main.cpp \
    authserver.cpp \
    authsocket.cpp \
    ../shared/opcodes/opcodes.cpp \
    ../worldserver/game/server/worldsession.cpp \
    ../shared/databases/mysqlconnection.cpp \
    ../shared/databases/authdatabase.cpp \
    ../shared/databases/database.cpp \
    ../shared/logs/log.cpp \
    ../shared/configuration/configuration.cpp \
    ../shared/configuration/configmgr.cpp \
    ../shared/packets/worldpacket.cpp \
    ../shared/databases/worlddatabase.cpp \
    ../shared/databases/chardatabase.cpp \
    ../shared/queues/worldqueue.cpp \
    ../shared/queues/authqueue.cpp \
    ../worldserver/game/handlers/characterhandler.cpp \
    ../worldserver/game/handlers/acounthandler.cpp \
    ../shared/servers/SocketReader.cpp \
    ../shared/utils/util.cpp \
    ../worldserver/game/world/ObjectFactory.cpp \
    ../worldserver/game/handlers/QueueHandler.cpp \
    ../worldserver/game/world/world.cpp

HEADERS += \
    ../shared/define.h \
    authserver.h \
    authsocket.h \
    ../shared/utils/util.h \
    ../shared/opcodes/opcodes.h \
    ../shared/packets/worldpacket.h \
    ../shared/packets/worldbuffer.h \
    ../worldserver/game/server/worldsession.h \
    ../shared/databases/mysqlconnection.h \
    ../shared/databases/authdatabase.h \
    ../shared/databases/database.h \
    ../shared/logs/log.h \
    ../shared/configuration/configuration.h \
    ../shared/configuration/configmgr.h \
    ../shared/databases/worlddatabase.h \
    ../shared/databases/chardatabase.h \
    ../shared/queues/worldqueue.h \
    ../shared/queues/authqueue.h \
    ../shared/servers/SocketReader.h \
    ../worldserver/game/world/ObjectFactory.h \
    ../worldserver/game/world/world.h \
    ../shared/utils/singleton.h
