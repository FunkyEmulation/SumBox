#ifndef WORLDQUEUE_H
#define WORLDQUEUE_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "utils/singleton.h"

class WorldSession;

typedef QList<WorldSession*> WorldClientList;

class WorldQueue : public Singleton<WorldQueue>
{
    Q_OBJECT

public:
    WorldQueue();
    ~WorldQueue();

    void Start();
    void Stop();

    void AddClient(WorldSession* socket);
    int GetClientsCount() { return m_clients.count(); }
    int GetClientPosition(WorldSession* socket) { return m_clients.indexOf(socket) + 1; }
    bool ClientInQueue(WorldSession* socket) { return GetClientPosition(socket) ? true : false; }

public slots:
    void RefreshQueue();

private:
    WorldClientList m_clients;
    QTimer* m_timer;
};

#endif // WORLDQUEUE_H
