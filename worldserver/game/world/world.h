#ifndef WORLD_H
#define WORLD_H

#include <QtCore>
#include "worldserver.h"
#include "logs/log.h"
#include "configuration/configmgr.h"

class WorldSession;

typedef QList<WorldSession*> SessionList;

class World
{
public:
    static World* Instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            mutex.lock();
            m_instance = new World;
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

    bool IsRunning() { return m_is_running; }

    void AddSession(WorldSession* session);
    void RemoveSession(WorldSession* session);

private:
    World();
    ~World();

    static World* m_instance;

    bool m_is_running;
    SessionList m_sessions;
};

#endif
