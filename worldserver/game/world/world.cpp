#include "world.h"

World* World::m_instance = 0;

World::World()
{
    StartServer();
    m_is_running = true;
}

World::~World()
{
    m_worldServer.Stop();
    m_is_running = false;
}

bool World::StartServer()
{
    if(!m_worldServer.Start(QHostAddress::LocalHost, quint16(ConfigMgr::World()->GetInt("WorldServerPort"))))
    {
        Log::Write(LOG_TYPE_NORMAL, m_worldServer.GetErrorString().toLatin1().data());
        return false;
    }
    else
       Log::Write(LOG_TYPE_NORMAL, "Worldserver started on port %i : waiting for connections", ConfigMgr::World()->GetInt("WorldServerPort"));

    return true;
}
