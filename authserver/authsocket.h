#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

class AuthSocket : QObject
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    void Disconnect() { m_socket->disconnect(); }
    
private slots:
    void OnRead();

private:
    QTcpSocket* m_socket;
};

#endif // AUTHSOCKET_H
