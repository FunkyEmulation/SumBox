#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/packets/worldpacket.h"
#include "AuthModel.h"

class AuthSocket : public QObject
{
    Q_OBJECT
public:
    AuthSocket(QTcpSocket* socket);
    void SendInitPacket();
    void SendPacket(WorldPacket packet);
    void ParsePacket(QString packet);
    void CheckVersion(QString version);
    void CheckAccount(QString ids);
    void SendInformations();
    void SendServers();
    void SendRandomName();

public slots:
    void OnRead();
    void OnClose();

signals:
    void CloseConnection();

private:
    QTcpSocket* m_socket;
    AuthModel* m_DbCon;
    QString m_packet;
    QString m_hashKey;
    quint16 m_blockSize;
    QMap<QString,QString> m_infos; // account - pseudo - password - gmlevel - servers - secret_question - secret_answer - logged - banned
    quint8 m_state; // 0=non authentifié / 1=version reçue / 2 = authentifié
};

#endif // AUTHSOCKET_H
