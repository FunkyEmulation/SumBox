#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include "authdatabase.h"
#include "chardatabase.h"
#include "worlddatabase.h"

class Database
{
public:
    static Database* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new Database;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    static AuthDatabase* Auth()
    {
        return Database::Instance()->GetAuthDatabase();
    }

    static CharDatabase* Char()
    {
        return Database::Instance()->GetCharDatabase();
    }

    static WorldDatabase* World()
    {
        return Database::Instance()->GetWorldDatabase();
    }

    bool OpenAuthDatabase();
    bool OpenCharDatabase();
    bool OpenWorldDatabase();

private:
    Database();
    ~Database();

    AuthDatabase* GetAuthDatabase()
    {
        return m_authDatabase;
    }

    CharDatabase* GetCharDatabase()
    {
        return m_charDatabase;
    }

    WorldDatabase* GetWorldDatabase()
    {
        return m_worldDatabase;
    }

    static Database* m_instance;

    AuthDatabase* m_authDatabase;
    CharDatabase* m_charDatabase;
    WorldDatabase* m_worldDatabase;
};

#endif
