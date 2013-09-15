#include <QCoreApplication>
#include <QtCore>
#include <csignal>

#include "Define.h"
#include "AuthServer.h"
#include "Databases/Database.h"
#include "Logs/Log.h"
#include "Configuration/ConfigMgr.h"

void stop(int /*s*/)
{
    Log::Write(LOG_TYPE_NORMAL, "Stopping SumBox::Authserver...");
    AuthServer::Instance()->Stop();
    AuthServer::Instance()->Delete();
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

    Log::Write(LOG_TYPE_NORMAL, "Starting SumBox::Authserver...");

    if (!ConfigMgr::Instance()->LoadAuthConfig("authserver.conf"))
        return close();

    Log::Instance()->Init(ConfigMgr::Auth()->GetUShort("LogConsoleLevel"), ConfigMgr::Auth()->GetUShort("LogFileLevel"), ConfigMgr::Auth()->GetQString("LogFile"));

    if (!Database::Instance()->OpenAuthDatabase())
        return close();

    if(!AuthServer::Instance()->Start(QHostAddress::LocalHost, quint16(ConfigMgr::Auth()->GetInt("AuthServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, AuthServer::Instance()->GetErrorString().toLatin1().data());
        return close();
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %i : waiting for connections", ConfigMgr::Auth()->GetInt("AuthServerPort"));

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Authserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    signal(SIGINT, &stop);
    signal(SIGTERM, &stop);
    return a.exec();
}
