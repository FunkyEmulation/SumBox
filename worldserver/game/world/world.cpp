#include "world.h"
#include "game/Entities/ObjectMgr.h"
#include "game/Maps/MapMgr.h"
#include "game/scripting/ScriptMgr.h"

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
    m_raceStartInfos.insert(0, sRaceStartInfos());

    QSqlQuery startDatas = Database::World()->Query(SELECT_RACE_START_INFOS);
    while(startDatas.next())
    {
        sRaceStartInfos curRaceStartInfos;
        curRaceStartInfos.race      = startDatas.value(startDatas.record().indexOf("race")).toUInt();
        curRaceStartInfos.map_id    = startDatas.value(startDatas.record().indexOf("map_id")).toUInt();
        curRaceStartInfos.cell_id   = startDatas.value(startDatas.record().indexOf("cell_id")).toUInt();

        m_raceStartInfos.insert(curRaceStartInfos.race, curRaceStartInfos);
    }
}

sRaceStartInfos World::GetRaceStartInfos(quint8 race)
{
    if(m_raceStartInfos.contains(race))
        return m_raceStartInfos.value(race);
    else
        return m_raceStartInfos.value(0);
}
