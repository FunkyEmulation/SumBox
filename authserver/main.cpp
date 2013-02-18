#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <QtXml>
#include <iostream>
#include <csignal>
#include "../shared/define.h"
#include "authserver.h"
#include "AuthConfig.h"

#include <QtSql>
#include "../shared/databases/database.h"
#include "../shared/logs/log.h"
#include "../shared/configuration/configuration.h"

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
    //if (!Configuration::Instance()->OpenFile("authserver.conf"))
    //    return 0;

    Log::Instance()->OpenFile("authserver.log");

    AuthConfig* Config = AuthConfig::getInstance("authconfig.xml");
    if(Config->Error())
        return 0;

    QMap<QString,QString> AuthConfiguration = Config->getConfig();

    Database* db = Database::Instance();
    if(db->Error())
        return 0;

    if(!authserver.Start(QHostAddress(AuthConfiguration["authIp"].toAscii().data()), AuthConfiguration["authPort"].toInt()))
    {
        Log::Write(LOG_TYPE_NORMAL, authserver.GetErrorString().toAscii().data());
        return 0;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "AuthServer started on port %s : waiting for connections", AuthConfiguration["authPort"].toAscii().data());

    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");
    Log::Write(LOG_TYPE_NORMAL, "SumBox::Authserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data());

    signal(SIGINT, &exit);
    return a.exec();
}
