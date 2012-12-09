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
    
public slots:
    void OnRead();
    void OnClose() { m_socket->deleteLater(); }

private:
    QTcpSocket* m_socket;
};

#endif // AUTHSOCKET_H
