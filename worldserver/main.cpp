#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <iostream>
#include <csignal>
#include <QtSql>

#include "define.h"
#include "databases/database.h"
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "game/chat/commandline.h"
#include "game/scripting/luaengine.h"

using namespace std;

WorldServer worldserver;

void exit(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Worldserver...");
    worldserver.Stop();
    QCoreApplication::exit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    cout << "Starting SumBox::WorldServer..." << endl;

    if (!ConfigMgr::Instance()->LoadAuthConfig("authserver.conf"))
        return 0;

    if (!ConfigMgr::Instance()->LoadWorldConfig("worldserver.conf"))
        return 0;

    Log::Instance()->Init(ConfigMgr::World()->GetUShort("LogConsoleLevel"), ConfigMgr::World()->GetUShort("LogFileLevel"), ConfigMgr::World()->GetQString("LogFile"));

    /*Chat::Instance();
    CommandLine commandLine(&a);
    commandLine.run();*/

    if (!Database::Instance()->OpenAuthDatabase())
        return 0;

    if (!Database::Instance()->OpenCharDatabase())
        return 0;

    if (!Database::Instance()->OpenWorldDatabase())
        return 0;

    LuaEngine::Instance()->StartEngine();

    if (!World::Instance())
        return 0;

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data());

    signal(SIGINT, &exit);
    return a.exec();
}
