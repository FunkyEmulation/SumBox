#include "Game/Scripting/ScriptMgr.h"
#include "Logs/Log.h"

class ScriptLoadTestScript : ServerScript
{
public:
    ScriptLoadTestScript() : ServerScript("example_loadtestscript")
    {
    }

    void OnLoad()
    {
        Log::Write(LOG_TYPE_NORMAL, "ScriptMgr:: Script ScriptLoadTestScript is loaded (hook OnLoad).");
    }
};

void AddScript_ScriptLoadTestScript()
{
    new ScriptLoadTestScript();
}
