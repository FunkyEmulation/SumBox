#ifndef AUTHQUEUE_H
#define AUTHQUEUE_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "logs/log.h"
#include "configuration/configmgr.h"
#include "authsocket.h"
#include "utils/singleton.h"

class AuthSocket;

typedef QList<AuthSocket*> AuthClientList;

class AuthQueue : public Singleton<AuthQueue>
{
    Q_OBJECT

public:
    AuthQueue();
    ~AuthQueue();

    void Start();
    void Stop();

    void AddClient(AuthSocket* socket);
    int GetClientsCount() { return m_clients.count(); }
    int GetClientPosition(AuthSocket* socket) { return m_clients.indexOf(socket) + 1; }
    bool ClientInQueue(AuthSocket* socket) { return GetClientPosition(socket) ? true : false; }

public slots:
    void RefreshQueue();

private:
    AuthClientList m_clients;
    QTimer* m_timer;
};

#endif // AUTHQUEUE_H
