#include "worldserver.h"
#include "game/world/world.h"

WorldServer* WorldServer::m_instance = 0;

WorldServer::WorldServer()
{
    m_server = new QTcpServer();
}

WorldServer::~WorldServer()
{
    delete m_server;
}

bool WorldServer::Start(QHostAddress address, quint16 port)
{
    if(!m_server->listen(address, port))
        return false;

    connect(m_server, SIGNAL(newConnection()), this, SLOT(OnConnect()));
    return true;
}

void WorldServer::Stop()
{
    Log::Close();
    m_server->close();
}

void WorldServer::OnConnect()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    WorldSession* session = new WorldSession(socket);
    World::Instance()->AddSession(session);
}
