#ifndef CHAT_H
#define CHAT_H

#include <QtCore>
#include "../../../shared/logs/log.h"

class Chat;

enum ChatSecurity
{
    SECURITY_PLAYER = 0,
    SECURITY_MODERATOR = 1,
    SECURITY_GAMEMASTER = 2,
    SECURITY_ADMINISTRATOR = 3
};

struct ChatCommand
{
    QString name;
    quint8 security;
    bool allowConsole;
    bool (Chat::*Handler)(QString args);
    QString description;
};

typedef QMap<QString, ChatCommand> ChatCommandMap;

class Chat
{
public:
    static Chat* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new Chat;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Close()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    bool ParseCommand(QString command);

    // Commands handlers
    bool HandleAccountCreateCommand(QString args);

private:
    Chat();
    ~Chat();

    static Chat* m_instance;
    ChatCommandMap m_chatCommands;
};

#endif
