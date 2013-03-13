#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QtCore>
#include <iostream>
#include "chat.h"

using namespace std;

class CommandLine : QThread
{
    Q_OBJECT
public:
    CommandLine(QObject* parent) : QThread(parent) {}

    virtual void run()
    {
        string input;
        char args[256];
        while (cin >> input)
        {
            cin.get(args, 256);
            QString command = QString::fromStdString(input);
            command += QString::fromStdString(args);

            Chat::Instance()->ParseCommand(command);
        }
    }
};

#endif
