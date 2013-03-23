#ifndef AUTHQUEUE_H
#define AUTHQUEUE_H

#include <QtCore>
#include "../shared/logs/log.h"
#include <QObject>
#include <QtNetwork>
#include "authsocket.h"

class AuthSocket;

typedef QList<AuthSocket*> ClientList;

class AuthQueue : public QObject
{
    Q_OBJECT

public:
    static AuthQueue* Instance();
    ClientList* GetClients();
    void AddClient(AuthSocket* socket);

public slots:
    void RefreshQueue();

private:
    static AuthQueue* m_instance;
    AuthQueue();
    ClientList* m_clients;
    QTimer* m_timer;

    void Start();
    void Stop();

};

#endif // AUTHQUEUE_H
