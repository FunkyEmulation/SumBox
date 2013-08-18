#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QtCore>
#include <iostream>
#include "chat.h"
#include "game/world/world.h"

using namespace std;

class CommandLine : QThread
{
    Q_OBJECT
public:
    CommandLine(QObject* parent) : QThread(parent) {}

    virtual void run()
    {
        printf("Sumbox>");

        string input;
        char args[256];
        while (World::Instance()->IsRunning())
        {
            fflush(stdout);

            char* command_str;
            char commandbuff[256];

            command_str = fgets(commandbuff, sizeof(commandbuff), stdin);

            if (command_str != NULL)
            {
                for (int x=0; command_str[x]; ++x)
                    if (command_str[x] == '\r' || command_str[x] == '\n')
                    {
                        command_str[x] = 0;
                        break;
                    }

                if (!*command_str)
                {
                    printf("Sumbox>");
                    continue;
                }


                QString command = QString::fromStdString(input);

                if (command.isEmpty())
                {
                    printf("Sumbox>");
                    continue;
                }

                fflush(stdout);
                Chat::Instance()->ParseCommand(command);
            }
            else if (feof(stdin))
            {
                World::Close();
            }
        }
    }
};

#endif
