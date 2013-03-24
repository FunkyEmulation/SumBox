#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <iostream>
#include <csignal>
#include "../shared/define.h"
#include "authserver.h"

#include <QtSql>
#include "../shared/databases/database.h"
#include "../shared/logs/log.h"
#include "../shared/configuration/configmgr.h"

using namespace std;

AuthServer authserver;

void exit(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Authserver...");
    authserver.Stop();
    QCoreApplication::exit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    cout << "Starting SumBox::Authserver..." << endl;

    if (!ConfigMgr::Instance()->LoadAuthConfig("authserver.conf"))
        return 0;

    Log::Instance()->Init();

    if (!Database::Instance()->OpenAuthDatabase())
        return 0;

    if(!authserver.Start(QHostAddress::LocalHost, quint16(ConfigMgr::Auth()->GetInt("AuthServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, authserver.GetErrorString().toAscii().data());
        return 0;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %i : waiting for connections", ConfigMgr::Auth()->GetInt("AuthServerPort"));

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Authserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data());

    signal(SIGINT, &exit);
    return a.exec();
}
