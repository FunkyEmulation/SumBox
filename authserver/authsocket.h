#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>

#include "Define.h"
#include "Databases/Database.h"
#include "Queues/AuthQueue.h"
#include "Network/SocketHandler.h"

class AuthSocket : public SocketHandler
{
    Q_OBJECT

public:
    AuthSocket(QTcpSocket* socket);
    ~AuthSocket();

    virtual void ProcessPacket(QString packet);
    void SendInitPacket();

    void CheckVersion(QString version);
    void CheckAccount();
    void SendInformations();
    void QueueManager();
    void SendPersos();
    void SelectServer(uint id);
    void SearchFriend(QString pseudo);

public slots:
    void OnClose();

private:
    QString m_idsPacket;
    QString m_hashKey;
    QMap<QString, QVariant> m_infos; // account - pseudo - password - gmlevel - servers - secret_question - secret_answer - logged - banned
    ClientState m_state;
};

#endif // AUTHSOCKET_H
