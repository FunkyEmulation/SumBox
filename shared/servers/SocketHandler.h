#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtNetwork>
#include <QTcpSocket>
#include "packets/worldpacket.h"
#include "opcodes/opcodes.h"

class WorldPacket;

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    SocketHandler(QTcpSocket* socket);

    QString GetIp() const
    {
        return m_socket->peerAddress().toString();
    }

    void SendPacket(WorldPacket& data);
    virtual void ProcessPacket(QString packet) = 0;

public slots:
    void OnRead();
    void OnClose();

protected:
    QTcpSocket* m_socket;
    QString m_packet;
};

#endif // SOCKETREADER_H
