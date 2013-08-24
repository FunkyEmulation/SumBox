#include "world.h"

template<> World*  Singleton<World>::m_instance = 0;

World::World()
{
    m_is_running = true;
}

World::~World()
{
    m_is_running = false;
}

void World::AddSession(WorldSession *session)
{
    m_sessions.push_back(session);
}

void World::RemoveSession(WorldSession* session)
{
    m_sessions.removeOne(session);
}
