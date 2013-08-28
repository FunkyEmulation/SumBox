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
    ../shared/databases/worlddatabase.cpp \
    ../shared/databases/chardatabase.cpp \
    ../shared/queues/worldqueue.cpp \
    ../shared/queues/authqueue.cpp \
    ../shared/utils/util.cpp \
    ../worldserver/game/handlers/QueueHandler.cpp \
    ../worldserver/game/world/world.cpp \
    ../shared/servers/SocketHandler.cpp \
    ../worldserver/game/Entities/ObjectMgr.cpp \
    ../worldserver/game/handlers/characterhandler.cpp \
    ../worldserver/game/Entities/Character/Character.cpp \
    ../worldserver/game/handlers/AccountHandler.cpp \
    ../worldserver/game/handlers/GameHandler.cpp \
    ../worldserver/game/Maps/MapMgr.cpp \
    ../worldserver/game/Maps/Map.cpp \
    ../worldserver/game/handlers/MiscHandler.cpp \
    ../worldserver/game/handlers/MapHandler.cpp \
    ../worldserver/game/Entities/Object/Object.cpp

HEADERS += \
    ../shared/define.h \
    authserver.h \
    authsocket.h \
    ../shared/utils/util.h \
    ../shared/opcodes/opcodes.h \
    ../shared/packets/worldpacket.h \
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
    ../worldserver/game/world/world.h \
    ../shared/utils/singleton.h \
    ../shared/servers/SocketHandler.h \
    ../worldserver/game/Entities/Object/Object.h \
    ../worldserver/game/Entities/ObjectMgr.h \
    ../worldserver/game/Entities/Unit/Unit.h \
    ../worldserver/game/Entities/Character/Character.h \
    ../worldserver/game/Maps/MapMgr.h \
    ../worldserver/game/Maps/Map.h
