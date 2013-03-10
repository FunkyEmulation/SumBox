#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"

class WorldPacket;

class WorldSession : public QObject
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    void SendPacket(WorldPacket packet);

    // Default handlers
    void HandleNULL(QString& /*packet*/) {}
    void HandleServerSide(QString& packet); // SMSG packets
    void HandleBeforeAuth(QString& packet); // CMSG packets before client auth (WorldSession don't exist at this moment)

    // Handlers
    void HandleTicketResponse(QString& packet);

public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
    QString m_packet;
};

#endif // WORLDSESSION_H
