#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "Logs/Log.h"
#include "Game/Server/WorldSession.h"
#include "Utils/Singleton.h"

class WorldServer : public Singleton<WorldServer>
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
};

#endif // WORLDSERVER_H
