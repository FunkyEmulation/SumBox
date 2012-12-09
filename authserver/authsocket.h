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
    void SendInitPacket();
    void SendPacket(QByteArray packet);
    
public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
};

#endif // AUTHSOCKET_H
