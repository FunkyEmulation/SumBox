#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QtCore>
#include <QtNetwork>

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
    void OnRead();
    void OnClose();

private:
    QTcpServer* m_server;
};

#endif // AUTHSERVER_H
