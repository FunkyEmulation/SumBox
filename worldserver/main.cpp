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

void stop(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Worldserver...");
    worldserver.Stop();
    QCoreApplication::exit();
}

int close()
{
    stop(0);
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    cout << "Starting SumBox::WorldServer..." << endl;

    if (!ConfigMgr::Instance()->LoadAuthConfig("authserver.conf"))
        return close();

    if (!ConfigMgr::Instance()->LoadWorldConfig("worldserver.conf"))
        return close();

    Log::Instance()->Init(ConfigMgr::World()->GetUShort("LogConsoleLevel"), ConfigMgr::World()->GetUShort("LogFileLevel"), ConfigMgr::World()->GetQString("LogFile"));

    /*Chat::Instance();
    CommandLine commandLine(&a);
    commandLine.run();*/

    if (!Database::Instance()->OpenAuthDatabase())
        return close();

    if (!Database::Instance()->OpenCharDatabase())
        return close();

    if (!Database::Instance()->OpenWorldDatabase())
        return close();

    LuaEngine::Instance()->StartEngine();

    if (!World::Instance())
        return close();

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
