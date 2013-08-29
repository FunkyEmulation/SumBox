#include "ScriptMgr.h"
#include "luaengine.h"
#include "ScriptLoader.h"

template<class T>
class ScriptRegistry
{
public:
    typedef QMap<quint32, T*> ScriptsMap;
    typedef typename ScriptsMap::Iterator ScriptsMapItr;
    static ScriptsMap ScriptsList;

    static void AddScript(T* const script)
    {
        ScriptsList[m_scriptIdCounter++] = script;
    }

private:
    static quint16 m_scriptIdCounter;
};

// Utility macros to refer to the script registry.
#define SCR_REG_MAP(T) ScriptRegistry<T>::ScriptsMap
#define SCR_REG_ITR(T) ScriptRegistry<T>::ScriptsMapItr
#define SCR_REG_LST(T) ScriptRegistry<T>::ScriptsList

// Utility macros for looping over scripts.
#define FOR_SCRIPTS(T, C, E) \
if (SCR_REG_LST(T).empty()) \
return; \
for (SCR_REG_ITR(T) C = SCR_REG_LST(T).begin(); \
C != SCR_REG_LST(T).end(); ++C)

#define FOR_SCRIPTS_RET(T, C, E, R) \
if (SCR_REG_LST(T).empty()) \
return R; \
for (SCR_REG_ITR(T) C = SCR_REG_LST(T).begin(); \
C != SCR_REG_LST(T).end(); ++C)

#define FOREACH_SCRIPT(T) \
FOR_SCRIPTS(T, itr, end) \
(*itr)

template<> ScriptMgr*  Singleton<ScriptMgr>::m_instance = 0;

ScriptMgr::ScriptMgr() {}
ScriptMgr::~ScriptMgr() {}

void ScriptMgr::Initialize()
{
    // Load C++ scripts
    LoadScripts();

    // Hook test
    ScriptMgr::Instance()->OnLoad();

    // Load LUA engine
    LuaEngine::Instance()->StartEngine();
}

void ScriptMgr::OnLoad()
{
    FOREACH_SCRIPT(ServerScript)->OnLoad();
}

ServerScript::ServerScript(const QString &name) : ScriptObject(name)
{
    ScriptRegistry<ServerScript>::AddScript(this);
}

// Instantiate static members of ScriptRegistry.
template<class T> QMap<quint32, T*> ScriptRegistry<T>::ScriptsList;
template<class T> quint16 ScriptRegistry<T>::m_scriptIdCounter = 0;

// Specialize for each script type class like so:
template class ScriptRegistry<ServerScript>;

// Undefine utility macros.
#undef FOREACH_SCRIPT
#undef FOR_SCRIPTS_RET
#undef FOR_SCRIPTS
#undef SCR_REG_LST
#undef SCR_REG_ITR
#undef SCR_REG_MAP
