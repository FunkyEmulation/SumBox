#ifndef LUAENGINE_H
#define LUAENGINE_H

#include <QtCore>
#include "logs/log.h"
#include "utils/singleton.h"

extern "C"
{
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
}

typedef QList<QString> LuaScriptsList;

class LuaEngine : public Singleton<LuaEngine>
{
public:
    LuaEngine();
    ~LuaEngine();

    void StartEngine();
    void LoadLuaScripts();
    void ReportState(lua_State* L);

private:
    lua_State* m_luaState;
    LuaScriptsList m_luaScripts;
};

#endif
