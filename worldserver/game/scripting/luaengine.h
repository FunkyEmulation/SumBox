#ifndef LUAENGINE_H
#define LUAENGINE_H

#include <QtCore>
#include "logs/log.h"

extern "C"
{
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
}

typedef QList<QString> LuaScriptsList;

class LuaEngine
{
public:
    static LuaEngine* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new LuaEngine;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Close()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    void StartEngine();
    void LoadLuaScripts();
    void ReportState(lua_State* L);

private:
    LuaEngine();
    ~LuaEngine();

    static LuaEngine* m_instance;

    lua_State* m_luaState;
    LuaScriptsList m_luaScripts;
};

#endif
