#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"

class AuthSocket : QObject
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    void SendInitPacket();
    void SendPacket(WorldPacket packet);
    void ParsePacket(QString packet);
    void CheckAccount(QString ids);

public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
    quint16 m_blockSize;
    QMap<QString,QString> m_infos; // pseudo - account - serveurs - gmlevel - question - version
    quint8 m_state; // 0=non authentifié / 1=version reçue / 2 = authentifié
};

#endif // AUTHSOCKET_H
