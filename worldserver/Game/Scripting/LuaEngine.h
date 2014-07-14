#ifndef LUAENGINE_H
#define LUAENGINE_H

#include <QtCore>

#include "Logs/Log.h"
#include "Utils/Singleton.h"
#include "lua/lua.hpp"

typedef QList<QString> LuaScriptsList;

class LuaEngine : public Singleton<LuaEngine>
{
public:
    LuaEngine();
    ~LuaEngine();

    void StartEngine(bool restart = false);
    void StopEngine();
    void LoadLuaScripts();
    void ReportState(lua_State* L);

private:
    lua_State* m_luaState;
    LuaScriptsList m_luaScripts;
};

#endif
