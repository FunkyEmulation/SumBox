#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QtCore>
#include "databases/database.h"
#include "objects/Account.h"
#include "objects/Character.h"

class Account;
class Character;

class ObjectFactory
{
public:
    static ObjectFactory* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new ObjectFactory;
            mutex.unlock();
        }
        return m_instance;
    }
    static void Close()
    {
        // TODO : delete des objets
    }

    Account* GetAccount(int id);
    Account* LoadAccount(QString key);
    Character* GetCharacter(int id);
    QList<Character*> LoadAccountCharacters(Account* const acc);
    Character* CreateCharacter(int account, QString name, int breed, int gender, int gfxId, char* color1, char* color2, char* color3);

private:
    static ObjectFactory* m_instance;

    QMap<int, Account*> m_accounts;
    QMap<int, Character*> m_characters;
};

#endif // OBJECTFACTORY_H
