#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <iostream>
#include <csignal>
#include <QtSql>

#include "Define.h"
#include "Databases/Database.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"
#include "Game/Chat/CommandLine.h"

using namespace std;

void stop(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Worldserver...");
    WorldServer::Instance()->Stop();
    World::Delete();

    WorldServer::Instance()->Delete();
    Log::Delete();
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

    if (!Database::Instance()->OpenAuthDatabase())
        return close();

    if (!Database::Instance()->OpenCharDatabase())
        return close();

    if (!Database::Instance()->OpenWorldDatabase())
        return close();

    if (!World::Instance()->Initialize())
    {
        Log::Write(LOG_TYPE_NORMAL, "World initialization failed. Exiting.");
        return close();
    }

    if(!WorldServer::Instance()->Start(QHostAddress::LocalHost, quint16(ConfigMgr::World()->GetInt("WorldServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, WorldServer::Instance()->GetErrorString().toLatin1().data());
        return close();
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "Worldserver started on port %i : waiting for connections", ConfigMgr::World()->GetInt("WorldServerPort"));

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    Chat::Instance();
    CommandLine commandLine(&a);
    commandLine.start();

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
