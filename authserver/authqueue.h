#ifndef AUTHQUEUE_H
#define AUTHQUEUE_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/logs/log.h"
#include "../shared/configuration/configmgr.h"
#include "authsocket.h"

class AuthSocket;

typedef QList<AuthSocket*> ClientList;

class AuthQueue : public QObject
{
    Q_OBJECT

public:
    static AuthQueue* Instance()
    {
        static QMutex mutex;
        if(m_instance == 0)
        {
            mutex.lock();
            m_instance = new AuthQueue;
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

    void AddClient(AuthSocket* socket);
    int GetClientsCount() { return m_clients.count(); }
    int GetClientPosition(AuthSocket* socket) { return m_clients.indexOf(socket) + 1; }
    bool ClientInQueue(AuthSocket* socket) { return GetClientPosition(socket) ? true : false; }

public slots:
    void RefreshQueue();

private:
    AuthQueue();
    ~AuthQueue();

    static AuthQueue* m_instance;    

    ClientList m_clients;
    QTimer* m_timer;
};

#endif // AUTHQUEUE_H
