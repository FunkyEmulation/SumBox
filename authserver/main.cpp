#include <QCoreApplication>
#include <QTime>
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();
    cout << "Starting SumBox::Authserver..." << endl;

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
