#include "World.h"
#include "Entities/ObjectMgr.h"
#include "Maps/MapMgr.h"
#include "Scripting/ScriptMgr.h"

template<> World*  Singleton<World>::m_instance = 0;

World::World()
{
    m_is_running = true;
}

World::~World()
{
    m_is_running = false;
    m_raceStartInfos.clear();

    MapMgr::Instance()->Delete();
}

bool World::Initialize()
{
    ObjectMgr::Instance()->SetHighestGuids();

    if (!MapMgr::Instance()->LoadFromDB())
        return false;

    LoadRaceStartInfos();

    ScriptMgr::Instance()->Initialize();

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

void World::LoadRaceStartInfos()
{
    m_raceStartInfos.clear();

    QSqlQuery result = Database::World()->Query(SELECT_RACE_START_INFOS);
    while (result.next())
    {
        quint8 race = (quint8)result.value(result.record().indexOf("race")).toUInt();

        sRaceStartInfos curRaceStartInfos;
        curRaceStartInfos.mapId    = (quint16)result.value(result.record().indexOf("map_id")).toUInt();
        curRaceStartInfos.cellId   = (quint16)result.value(result.record().indexOf("cell_id")).toUInt();

        m_raceStartInfos.insert(race, curRaceStartInfos);
    }
}

sRaceStartInfos World::GetRaceStartInfos(quint8 race)
{
    return m_raceStartInfos.value(race);
}
