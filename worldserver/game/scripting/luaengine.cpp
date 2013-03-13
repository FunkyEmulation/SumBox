#include "luaengine.h"

LuaEngine* LuaEngine::m_instance = 0;

LuaEngine::LuaEngine()
{
    m_luaState = NULL;
}

LuaEngine::~LuaEngine()
{
    lua_close(m_luaState);
    m_luaState = NULL;
}

void LuaEngine::StartEngine()
{
    Log::Write(LOG_TYPE_NORMAL, "Starting Lua Engine...");
    m_luaState = luaL_newstate();
    LoadLuaScripts();
    luaL_openlibs(m_luaState);

    LuaScriptsList::ConstIterator itr;
    for (itr = m_luaScripts.begin(); itr != m_luaScripts.end(); ++itr)
    {
        QString fileName = (*itr);

        if (luaL_loadfile(m_luaState, fileName.toAscii().data()) != 0)
        {
            Log::Write(LOG_TYPE_NORMAL, "LuaEngine::Error while loading %s script.", fileName.toAscii().data());
            ReportState(m_luaState);
        }
        else
        {
            int err = lua_pcall(m_luaState, 0, 0, 0);
            if (err != 0 && err == LUA_ERRRUN)
            {
                Log::Write(LOG_TYPE_NORMAL, "LuaEngine::Error while loading %s script.", fileName.toAscii().data());
                ReportState(m_luaState);
            }
        }
    }
}

void LuaEngine::LoadLuaScripts()
{
    Log::Write(LOG_TYPE_NORMAL, "Load Lua Scripts...");

    // TODO : add to config file
    QString directory = "luascripts";
    QDir luaDirectory(directory);

    if (!luaDirectory.exists())
        Log::Write(LOG_TYPE_NORMAL, "Lua Scripts \"%s\" directory not found !", directory.toAscii().data());
    else
    {
        QStringList luaScripts = luaDirectory.entryList(QStringList("*.lua"));

        QStringList::ConstIterator itr;
        for (itr = luaScripts.begin(); itr != luaScripts.end(); ++itr)
        {
            QString path = directory + "/" + (*itr);
            m_luaScripts.push_back(path);
        }
    }

    Log::Write(LOG_TYPE_NORMAL, "Loaded %u Lua Scripts.", m_luaScripts.size());
}

void LuaEngine::ReportState(lua_State *L)
{
    const char* error = lua_tostring(L, -1);
    while (error)
    {
        lua_pop(L, -1);
        Log::Write(LOG_TYPE_NORMAL, "Lua::Error : %s", error);
        error = lua_tostring(L, -1);
    }
}
