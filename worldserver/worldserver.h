#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include "logs/log.h"
#include "game/server/worldsession.h"

class WorldServer : QObject
{
    Q_OBJECT
public:
    static WorldServer* Instance()
    {
        static QMutex mutex;
        if(m_instance == 0)
        {
            mutex.lock();
            m_instance = new WorldServer;
            mutex.unlock();
        }
        return m_instance;
    }

    static void Drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_instance;
        mutex.unlock();
    }

    QString GetErrorString() { return m_server->errorString(); }
    bool Start(QHostAddress address, quint16 port);
    void Stop();

private slots:
    void OnConnect();

private:
    WorldServer();
    ~WorldServer();

    static WorldServer* m_instance;

    QTcpServer* m_server;
};

#endif // WORLDSERVER_H
