#include <QCoreApplication>
#include <QTime>

#include <QFile>
#include <QtXml>
#include <iostream>
#include <csignal>
#include "../shared/define.h"
#include "authserver.h"
#include "AuthConfig.h"
#include "AuthModel.h"

using namespace std;

AuthServer authserver;

void exit(int /*s*/)
{
    cout << "Stopping SumBox::Authserver..." << endl;
    authserver.Stop();
    cout << "SumBox::Authserver stopped. Exiting..." << endl;
    QCoreApplication::exit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();
    cout << "Starting SumBox::Authserver..." << endl;

    AuthConfig* Config = AuthConfig::getInstance("authconfig.xml");
    if(Config->Error())
        return 0;

    QMap<QString,QString> AuthConfiguration = Config->getConfig();

    AuthModel* DbCon = AuthModel::getInstance(AuthConfiguration["authDbHost"],
                                             AuthConfiguration["authDbUser"],
                                             AuthConfiguration["authDbPswd"],
                                             AuthConfiguration["authDbName"]);

    if(DbCon->Error())
        return 0;

    if(!authserver.Start(QHostAddress(AuthConfiguration["authIp"].toAscii().data()), AuthConfiguration["authPort"].toInt()))
    {
        cout << authserver.GetErrorString().toAscii().data() << endl;
        return 0;
    }
    else
       cout << "AuthServer started on port " << AuthConfiguration["authPort"].toAscii().data() << " : waiting for connections" << endl;

    cout << "Press ctrl + c to quit." << endl;
    cout << "SumBox::Authserver started in " << QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data() << " sec." << endl;

    signal(SIGINT, &exit);
    return a.exec();
}
