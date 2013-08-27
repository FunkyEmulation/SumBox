#include "world.h"
#include "game/Entities/ObjectMgr.h"
#include "game/Maps/MapMgr.h"

template<> World*  Singleton<World>::m_instance = 0;

World::World()
{
    m_is_running = true;
}

World::~World()
{
    m_is_running = false;

    MapMgr::Instance()->Delete();
}

bool World::Initialize()
{
    ObjectMgr::Instance()->SetHighestGuids();

    if (!MapMgr::Instance()->LoadFromDB())
        return false;

    return true;
}

void World::AddSession(WorldSession *session)
{
    m_sessions.push_back(session);
}

void World::RemoveSession(WorldSession* session)
{
    m_sessions.removeOne(session);
}
