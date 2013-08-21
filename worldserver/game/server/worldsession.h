#ifndef WORLDSESSION_H
#define WORLDSESSION_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "databases/database.h"
#include "queues/worldqueue.h"
#include "define.h"
#include "servers/SocketReader.h"
#include "game/world/ObjectFactory.h"

class WorldSession : public SocketReader
{
    Q_OBJECT
public:
    WorldSession(QTcpSocket* socket);
    ~WorldSession();

    virtual void ProcessPacket(QString packet);

    // Default handlers
    void HandleNULL(QString& /*packet*/) {}
    void HandleServerSide(QString& /*packet*/) {} // SMSG packets
    void HandleBeforeAuth(QString& /*packet*/) {} // CMSG packets before client auth (WorldSession don't exist at this moment)

    // Handlers
    void HandleQueuePosition(QString& packet);
    void HandleTicketResponse(QString& packet);     // Vérifie la clé de connection et initialise les détails compte :
    void HandleRegionalVersion(QString& packet);    // ?
    void HandleListGifts(QString& packet);          // Gère la liste des cadeaux du compte. A faire
    void HandleKey(QString& packet);                // Stocke la clé de cryptage renseignée par le client
    void HandleCharactersList(QString& packet);     // Met en file d'attente :
    void HandleSendCharacterList(QString& packet);  // Gère la liste des personnages du serveur actuel
    void HandleRandomPseudo(QString& packet);       // Génère un pseudo aléatoire
    void HandleCreatePerso(QString& packet);        // Crée un nouveau perso

    void SendCharacterList(); // Envoit la liste des personnages du compte
    void HandleDeleteChar(QString& packet); // Supprime un personnage
    void HandleSelectChar(QString& packet); // Sélection d'un personnage pour entrer en jeux


public slots:
    void OnClose();

private:
    Account* m_account;
    ClientState m_state;
    QString m_ticket; // Avant connection
};

#endif // WORLDSESSION_H
