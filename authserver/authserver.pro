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
    ../worldserver/game/Entities/Object/Object.cpp \
    ../worldserver/game/scripting/ScriptMgr.cpp \
    ../worldserver/game/scripting/ScriptLoader.cpp \
    ../worldserver/game/scripting/luaengine.cpp \
    ../worldserver/game/scripting/lua/lzio.c \
    ../worldserver/game/scripting/lua/lvm.c \
    ../worldserver/game/scripting/lua/lundump.c \
    ../worldserver/game/scripting/lua/ltm.c \
    ../worldserver/game/scripting/lua/ltablib.c \
    ../worldserver/game/scripting/lua/ltable.c \
    ../worldserver/game/scripting/lua/lstrlib.c \
    ../worldserver/game/scripting/lua/lstring.c \
    ../worldserver/game/scripting/lua/lstate.c \
    ../worldserver/game/scripting/lua/lparser.c \
    ../worldserver/game/scripting/lua/loslib.c \
    ../worldserver/game/scripting/lua/lopcodes.c \
    ../worldserver/game/scripting/lua/lobject.c \
    ../worldserver/game/scripting/lua/loadlib.c \
    ../worldserver/game/scripting/lua/lmem.c \
    ../worldserver/game/scripting/lua/lmathlib.c \
    ../worldserver/game/scripting/lua/llex.c \
    ../worldserver/game/scripting/lua/liolib.c \
    ../worldserver/game/scripting/lua/linit.c \
    ../worldserver/game/scripting/lua/lgc.c \
    ../worldserver/game/scripting/lua/lfunc.c \
    ../worldserver/game/scripting/lua/ldump.c \
    ../worldserver/game/scripting/lua/ldo.c \
    ../worldserver/game/scripting/lua/ldebug.c \
    ../worldserver/game/scripting/lua/ldblib.c \
    ../worldserver/game/scripting/lua/lctype.c \
    ../worldserver/game/scripting/lua/lcorolib.c \
    ../worldserver/game/scripting/lua/lcode.c \
    ../worldserver/game/scripting/lua/lbitlib.c \
    ../worldserver/game/scripting/lua/lbaselib.c \
    ../worldserver/game/scripting/lua/lauxlib.c \
    ../worldserver/game/scripting/lua/lapi.c \
    ../worldserver/Scripts/Examples/ScriptLoadTest.cpp \
    ../worldserver/game/Entities/Unit/Unit.cpp

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
    ../worldserver/game/Maps/Map.h \
    ../worldserver/game/scripting/ScriptMgr.h \
    ../worldserver/game/scripting/ScriptLoader.h \
    ../worldserver/game/scripting/luaengine.h \
    ../worldserver/game/scripting/lua/lzio.h \
    ../worldserver/game/scripting/lua/lvm.h \
    ../worldserver/game/scripting/lua/lundump.h \
    ../worldserver/game/scripting/lua/lualib.h \
    ../worldserver/game/scripting/lua/luaconf.h \
    ../worldserver/game/scripting/lua/lua.hpp \
    ../worldserver/game/scripting/lua/lua.h \
    ../worldserver/game/scripting/lua/ltm.h \
    ../worldserver/game/scripting/lua/ltable.h \
    ../worldserver/game/scripting/lua/lstring.h \
    ../worldserver/game/scripting/lua/lstate.h \
    ../worldserver/game/scripting/lua/lparser.h \
    ../worldserver/game/scripting/lua/lopcodes.h \
    ../worldserver/game/scripting/lua/lobject.h \
    ../worldserver/game/scripting/lua/lmem.h \
    ../worldserver/game/scripting/lua/llimits.h \
    ../worldserver/game/scripting/lua/llex.h \
    ../worldserver/game/scripting/lua/lgc.h \
    ../worldserver/game/scripting/lua/lfunc.h \
    ../worldserver/game/scripting/lua/ldo.h \
    ../worldserver/game/scripting/lua/ldebug.h \
    ../worldserver/game/scripting/lua/lctype.h \
    ../worldserver/game/scripting/lua/lcode.h \
    ../worldserver/game/scripting/lua/lauxlib.h \
    ../worldserver/game/scripting/lua/lapi.h
