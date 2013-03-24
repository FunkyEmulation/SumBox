#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"
#include "../shared/databases/database.h"
#include "../shared/queues/worldqueue.h"
#include "../shared/define.h"

class WorldPacket;

class WorldSession : public QObject
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    QString GetIp() const
    {
        return m_socket->peerAddress().toString();
    }
    void SendPacket(WorldPacket packet);

    // Default handlers
    void HandleNULL(QString& /*packet*/) {}
    void HandleServerSide(QString& /*packet*/) {} // SMSG packets
    void HandleBeforeAuth(QString& /*packet*/) {} // CMSG packets before client auth (WorldSession don't exist at this moment)

    // Handlers
    void HandleQueue(QString& packet);
    // Vérifie la clé de connection et initialise les détails compte :
    void HandleTicketResponse(QString& packet);
    // ?
    void HandleRegionalVersion(QString& packet);
    // Gère la liste des cadeaux du compte. A faire
    void HandleListGifts(QString& packet);
    // Stocke la clé de cryptage renseignée par le client
    void HandleKey(QString& packet);
    // Met en file d'attente :
    void HandleCharactersList(QString& packet);
    // Gère la liste des personnages du serveur actuel
    void SendCharacters();
    // Génère un pseudo aléatoire
    void HandleRandomPseudo(QString& packet);
    // Crée un nouveau perso
    void HandleCreatePerso(QString& packet);

public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
    QString m_packet;
    QMap<QString, QVariant> m_infos;
    ClientState m_state;
    QString m_ticket; // Avant connection
};

#endif // WORLDSESSION_H
