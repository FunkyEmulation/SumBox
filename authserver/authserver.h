#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "authsocket.h"
#include "../shared/logs/log.h"

typedef QList<AuthSocket*> SocketList;

class AuthServer : QObject
{
    Q_OBJECT
public:
    static AuthServer* Instance()
    {
        static QMutex mutex;
        if(m_instance == 0)
        {
            mutex.lock();
            m_instance = new AuthServer;
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

    QString GetErrorString() { return m_server->errorString(); }
    bool Start(QHostAddress address, quint16 port);
    void Stop();
    void RemoveSocket(AuthSocket* socket);

private slots:
    void OnConnect();

private:
    AuthServer();
    ~AuthServer();

    static AuthServer* m_instance;

    QTcpServer* m_server;
    SocketList m_sockets;
};

#endif // AUTHSERVER_H
