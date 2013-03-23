#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"
#include "../shared/databases/database.h"

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
    void HandleServerSide(QString& /*packet*/) {} // SMSG packets
    void HandleBeforeAuth(QString& /*packet*/) {} // CMSG packets before client auth (WorldSession don't exist at this moment)

    // Handlers
    // Vérifie la clé de connection et initialise les détails compte :
    void HandleTicketResponse(QString& packet);
    // ?
    void HandleRegionalVersion(QString& packet);
    // Gère la liste des cadeaux du compte. A faire
    void HandleListGifts(QString& packet);
    // Stocke la clé de cryptage renseignée par le client
    void HandleKey(QString& packet);
    // Gère la liste des personnages du serveur actuel
    void HandleCharactersList(QString& packet);

public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
    QString m_packet;
    QMap<QString, QVariant> m_infos;
};

#endif // WORLDSESSION_H
