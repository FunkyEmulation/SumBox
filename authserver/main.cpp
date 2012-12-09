#include <QCoreApplication>
#include <QTime>
#include <iostream>
#include "../shared/define.h"
#include "authserver.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();
    cout << "Starting SumBox::Authserver..." << endl;

    AuthServer authServer;
    if(!authServer.Start(QHostAddress("127.0.0.1"), 443))
    {
        cout << authServer.GetErrorString().toAscii().data() << endl;
        return 0;
    }
    else
        cout << "AuthServer started : waiting for connections" << endl;

    cout << "Press ctrl + c to quit." << endl;
    cout << "Started in " << QString::number(t.elapsed() / IN_MILLISECONDS).toAscii().data() << " sec." << endl;

    return a.exec();
}
