#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include "authdatabase.h"

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

    bool Error()
    {
        return m_error;
    }

private:
    Database();
    ~Database();

    AuthDatabase* GetAuthDatabase()
    {
        return m_authDatabase;
    }

    static Database* m_instance;
    AuthDatabase* m_authDatabase;

    bool m_error;
};

#endif
