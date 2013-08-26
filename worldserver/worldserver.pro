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

INCLUDEPATH += . ../shared ../worldserver
DEPENDPATH += . ../shared ../worldserver

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
    ../shared/databases/worlddatabase.cpp \
    ../shared/databases/chardatabase.cpp \
    game/chat/chat.cpp \
    game/scripting/luaengine.cpp \
    game/scripting/lua/lzio.c \
    game/scripting/lua/lvm.c \
    game/scripting/lua/lundump.c \
    game/scripting/lua/ltm.c \
    game/scripting/lua/ltablib.c \
    game/scripting/lua/ltable.c \
    game/scripting/lua/lstrlib.c \
    game/scripting/lua/lstring.c \
    game/scripting/lua/lstate.c \
    game/scripting/lua/lparser.c \
    game/scripting/lua/loslib.c \
    game/scripting/lua/lopcodes.c \
    game/scripting/lua/lobject.c \
    game/scripting/lua/loadlib.c \
    game/scripting/lua/lmem.c \
    game/scripting/lua/lmathlib.c \
    game/scripting/lua/llex.c \
    game/scripting/lua/liolib.c \
    game/scripting/lua/linit.c \
    game/scripting/lua/lgc.c \
    game/scripting/lua/lfunc.c \
    game/scripting/lua/ldump.c \
    game/scripting/lua/ldo.c \
    game/scripting/lua/ldebug.c \
    game/scripting/lua/ldblib.c \
    game/scripting/lua/lctype.c \
    game/scripting/lua/lcorolib.c \
    game/scripting/lua/lcode.c \
    game/scripting/lua/lbitlib.c \
    game/scripting/lua/lbaselib.c \
    game/scripting/lua/lauxlib.c \
    game/scripting/lua/lapi.c \
    game/world/world.cpp \
    ../shared/queues/worldqueue.cpp \
    game/handlers/characterhandler.cpp \
    ../shared/utils/util.cpp \
    game/handlers/QueueHandler.cpp \
    game/Accounts/AccountMgr.cpp \
    game/Entities/Character/Character.cpp \
    ../shared/servers/SocketHandler.cpp \
    game/Entities/ObjectMgr.cpp \
    game/handlers/AccountHandler.cpp \
    game/handlers/GameHandler.cpp

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
    ../shared/utils/util.h \
    ../shared/databases/worlddatabase.h \
    ../shared/databases/chardatabase.h \
    game/chat/commandline.h \
    game/chat/chat.h \
    game/scripting/luaengine.h \
    game/scripting/lua/lzio.h \
    game/scripting/lua/lvm.h \
    game/scripting/lua/lundump.h \
    game/scripting/lua/lualib.h \
    game/scripting/lua/luaconf.h \
    game/scripting/lua/lua.hpp \
    game/scripting/lua/lua.h \
    game/scripting/lua/ltm.h \
    game/scripting/lua/ltable.h \
    game/scripting/lua/lstring.h \
    game/scripting/lua/lstate.h \
    game/scripting/lua/lparser.h \
    game/scripting/lua/lopcodes.h \
    game/scripting/lua/lobject.h \
    game/scripting/lua/lmem.h \
    game/scripting/lua/llimits.h \
    game/scripting/lua/llex.h \
    game/scripting/lua/lgc.h \
    game/scripting/lua/lfunc.h \
    game/scripting/lua/ldo.h \
    game/scripting/lua/ldebug.h \
    game/scripting/lua/lctype.h \
    game/scripting/lua/lcode.h \
    game/scripting/lua/lauxlib.h \
    game/scripting/lua/lapi.h \
    game/world/world.h \
    ../shared/queues/worldqueue.h \
    game/Accounts/AccountMgr.h \
    game/Entities/Character/Character.h \
    ../shared/servers/SocketHandler.h \
    game/Entities/Object/Object.h \
    game/Entities/Unit/Unit.h \
    game/Entities/ObjectMgr.h \
    ../shared/utils/singleton.h
