#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QtNetwork>

#include "AuthSocket.h"
#include "Logs/Log.h"
#include "Utils/Singleton.h"

typedef QList<AuthSocket*> SocketList;

class AuthServer : public Singleton<AuthServer>
{
    Q_OBJECT
public:
    AuthServer();
    ~AuthServer();

    QString GetErrorString() { return m_server->errorString(); }
    bool Start(QHostAddress address, quint16 port);
    void Stop();
    void RemoveSocket(AuthSocket* socket);

private slots:
    void OnConnect();

private:
    QTcpServer* m_server;
    SocketList m_sockets;
};

#endif // AUTHSERVER_H
