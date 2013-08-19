#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <iostream>
#include <csignal>
#include "define.h"
#include "authserver.h"

#include <QtSql>
#include "databases/database.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

using namespace std;

void exit(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Authserver...");
    AuthServer::Instance()->Stop();
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

    Log::Instance()->Init(ConfigMgr::Auth()->GetUShort("LogConsoleLevel"), ConfigMgr::Auth()->GetUShort("LogFileLevel"), ConfigMgr::Auth()->GetQString("LogFile"));

    if (!Database::Instance()->OpenAuthDatabase())
        return 0;

    if(!AuthServer::Instance()->Start(QHostAddress::LocalHost, quint16(ConfigMgr::Auth()->GetInt("AuthServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, AuthServer::Instance()->GetErrorString().toLatin1().data());
        return 0;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %i : waiting for connections", ConfigMgr::Auth()->GetInt("AuthServerPort"));

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Authserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &exit);
    return a.exec();
}
