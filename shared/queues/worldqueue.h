#ifndef WORLDQUEUE_H
#define WORLDQUEUE_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/logs/log.h"
#include "../shared/configuration/configmgr.h"
#include "../../worldserver/game/server/worldsession.h"

class WorldSession;

typedef QList<WorldSession*> WorldClientList;

class WorldQueue : public QObject
{
    Q_OBJECT

public:
    static WorldQueue* Instance()
    {
        static QMutex mutex;
        if(m_instance == 0)
        {
            mutex.lock();
            m_instance = new WorldQueue;
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

    void Start();
    void Stop();

    void AddClient(WorldSession* socket);
    int GetClientsCount() { return m_clients.count(); }
    int GetClientPosition(WorldSession* socket) { return m_clients.indexOf(socket) + 1; }
    bool ClientInQueue(WorldSession* socket) { return GetClientPosition(socket) ? true : false; }

public slots:
    void RefreshQueue();

private:
    WorldQueue();
    ~WorldQueue();

    static WorldQueue* m_instance;

    WorldClientList m_clients;
    QTimer* m_timer;
};

#endif // WORLDQUEUE_H
