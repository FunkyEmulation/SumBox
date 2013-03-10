#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "../shared/logs/log.h"
#include "game/server/worldsession.h"

typedef QList<WorldSession*> SessionList;

class WorldServer : QObject
{
    Q_OBJECT
public:
    WorldServer();
    ~WorldServer();

    QString GetErrorString() { return m_server->errorString(); }
    bool Start(QHostAddress address, quint16 port);
    void Stop();

private slots:
    void OnConnect();

private:
    QTcpServer* m_server;
    SessionList m_sessions;
};

#endif // WORLDSERVER_H
