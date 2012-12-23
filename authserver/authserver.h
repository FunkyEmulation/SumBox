#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "authsocket.h"

typedef QList<AuthSocket*> SocketList;

class AuthServer : QObject
{
    Q_OBJECT
public:
    AuthServer();
    ~AuthServer();

    QString GetErrorString() { return m_server->errorString(); }
    bool Start(QHostAddress address, quint16 port);
    void Stop();

private slots:
    void OnConnect();
    void DelSockObject();

private:
    QTcpServer* m_server;
    SocketList m_sockets;
};

#endif // AUTHSERVER_H
