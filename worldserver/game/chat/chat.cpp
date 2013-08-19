#include "chat.h"

Chat* Chat::m_instance = 0;

static ChatCommand commandTable[] =
{
    { "caccount",   SECURITY_ADMINISTRATOR, true, &Chat::HandleAccountCreateCommand, "Create a new account. Syntax : .caccount \"username\" \"password\"" },
    { NULL,         0,                      false, NULL,                             NULL }
};

Chat::Chat()
{
    for (quint8 i = 0; commandTable[i].name != NULL; ++i)
        m_chatCommands[commandTable[i].name] = commandTable[i];
}

Chat::~Chat()
{
    m_chatCommands.clear();
}

bool Chat::ParseCommand(QString command)
{
    if (command.left(1) == ".")
    {
        command.remove(0, 1);
        QString commandName = command.split(" ").at(0);

        ChatCommandMap::ConstIterator itr = m_chatCommands.find(commandName);
        if (itr != m_chatCommands.end())
        {
            ChatCommand chatCommand = *itr;
            if (!(this->*chatCommand.Handler)(command))
                Log::Write(LOG_TYPE_NORMAL, chatCommand.description);

            return true;
        }

        Log::Write(LOG_TYPE_NORMAL, "Command \"%s\" don't exist.", commandName.toAscii().data());
    }

    return false;
}

bool Chat::HandleAccountCreateCommand(QString args)
{
    QStringList list = args.split(" ");

    if (list.size() < 3)
        return false;

    QString username = list.at(1);
    QString password = list.at(2);
    username.remove("\"");
    password.remove("\"");

    if (username.isEmpty() || password.isEmpty())
        return false;

    // TODO : Add account in DB
}
