#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"
#include "../shared/databases/database.h"

class AuthSocket : public QObject
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    void SendInitPacket();
    void SendPacket(WorldPacket packet);
    void ParsePacket(QString packet);

    void IsBanned(QString);

    void CheckVersion(QString version);
    void CheckAccount(QString ids);
    void SendInformations();
    void QueueManager();
    void SendPersos();
    void SendRandomName();
    void SelectServer(uint id);

public slots:
    void OnRead();
    void OnClose();

private:
    QTcpSocket* m_socket;
    QString m_packet;
    QString m_hashKey;
    QMap<QString, QVariant> m_infos; // account - pseudo - password - gmlevel - servers - secret_question - secret_answer - logged - banned
    quint8 m_state; // 0=non authentifié : attente de la version / 1=version reçue : attente des ids / 2 = ids reçus
};

#endif // AUTHSOCKET_H
