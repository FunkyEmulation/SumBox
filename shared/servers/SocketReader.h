#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QtNetwork>
#include <QTcpSocket>
#include "packets/worldpacket.h"
#include "opcodes/opcodes.h"

class WorldPacket;

class SocketReader : public QObject
{
    Q_OBJECT
public:
    SocketReader(QTcpSocket* socket);

    QString GetIp() const
    {
        return m_socket->peerAddress().toString();
    }

    void SendPacket(WorldPacket data);

public slots:
    void OnRead();
    void OnClose();

protected:
    QTcpSocket* m_socket;
    QString m_packet;

    virtual void ProcessPacket(QString packet) = 0;
};

#endif // SOCKETREADER_H
