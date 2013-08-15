#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"
#include "../shared/databases/database.h"
#include "../shared/queues/authqueue.h"
#include "servers/SocketReader.h"

class AuthSocket : private SocketReader
{
    Q_OBJECT

public:
    AuthSocket(QTcpSocket* socket);
    ~AuthSocket();

    QString GetIp() const { return m_socket->peerAddress().toString(); }

    void SendPacket(WorldPacket packet);

    void SendInitPacket();

    void CheckVersion(QString version);
    void CheckAccount();
    void SendInformations();
    void QueueManager();
    void SendPersos();
    void SelectServer(uint id);

public slots:
    void OnClose();

private:
    QString m_idsPacket;
    QString m_hashKey;
    QMap<QString, QVariant> m_infos; // account - pseudo - password - gmlevel - servers - secret_question - secret_answer - logged - banned
    ClientState m_state;

    virtual void ProcessPacket(QString packet);
};

#endif // AUTHSOCKET_H
