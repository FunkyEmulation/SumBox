#include <QCoreApplication>
#include <QTime>
#include <QFile>
#include <QtXml>
#include <iostream>
#include <csignal>
#include "../shared/define.h"
#include "authserver.h"

using namespace std;

AuthServer authserver;

void exit(int /*s*/)
{
    cout << "Stopping SumBox::Authserver..." << endl;
    authserver.Stop();
    cout << "SumBox::Authserver stopped. Exiting..." << endl;
    QCoreApplication::exit();
}

map loadAuthConfiguration(QString confName)
{
 map<string,string> AuthConfiguration;

    QDomDocument configDocument("AuthConfiguration");
       QFile file(confName);
       if(!file.open(QIODevice::ReadOnly))
       {
           cout << "Error: Non-existent auth configuration file '" << confName << "'..." << endl;
           file.close();
           return false;
       }
       if(!configDocument.setContent(&file))
       {
           cout << "Invalid xml configuration ..." << endl;
           file.close();
           return false;
       }
       file.close();
       QDomElement configElement = configDocument.documentElement();

       QDomNode node = configElement.firstChild(); // Premier noeud

       while(!node.isNull()) // parcourt ...
       {
           QDomElement curEl = node.toElement();
           if(!curEl.isNull())
               AuthConfiguration[curEl.tagName()] = curEl.text();
           node = node.nextSibling(); // On va  l'lment suivant
       }

    return AuthConfiguration;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    map<string,string> AuthConfiguration;
    QTime t;
    t.start();
    cout << "Starting SumBox::Authserver..." << endl;

    if(!AuthConfiguration = loadAuthConfiguration("auth_config.xml"))
        exit();

    if(!authserver.Start(QHostAddress("127.0.0.1"), 443))
    {
        cout << authserver.GetErrorString().toAscii().data() << endl;
        return 0;
    }
    else
        cout << "AuthServer started : waiting for connections" << endl;

    cout << "Press ctrl + c to quit." << endl;
    cout << "SumBox::Authserver started in " << QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data() << " sec." << endl;

    signal(SIGINT, &exit);
    return a.exec();
}
