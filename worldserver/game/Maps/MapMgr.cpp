#include "MapMgr.h"
#include "logs/log.h"
#include "define.h"

template<> MapMgr*  Singleton<MapMgr>::m_instance = 0;

MapMgr::MapMgr()
{
    m_mapsDataList.clear();
    m_mapsList.clear();

    Map* newMap = new Map();
    m_mapsList.insert(1, newMap);
}

MapMgr::~MapMgr()
{
    m_mapsDataList.clear();

    for (MapsList::Iterator itr = m_mapsList.begin(); itr != m_mapsList.end(); ++itr)
    {
        delete (*itr);
        (*itr) = NULL;
    }
    m_mapsList.clear();
}

bool MapMgr::LoadFromDB()
{
    Log::Write(LOG_TYPE_NORMAL, "MapMgr: loading maps...");
    QTime t;
    t.start();

    QSqlQuery result = Database::World()->Query(SELECT_ALL_MAPS);
    if (!result.first())
        return false;

    QSqlRecord rows = result.record();

    while (result.next())
    {
        sMapData mapData;
        quint16 mapId           = (quint16)result.value(rows.indexOf("id")).toUInt();

        mapData.date            = result.value(rows.indexOf("mapDate")).toString();
        mapData.width           = (quint8)result.value(rows.indexOf("width")).toUInt();
        mapData.height          = (quint8)result.value(rows.indexOf("height")).toUInt();
        mapData.places          = result.value(rows.indexOf("places")).toString();
        mapData.key             = result.value(rows.indexOf("mapKey")).toString();
        mapData.data            = result.value(rows.indexOf("mapData")).toString();
        mapData.cells           = result.value(rows.indexOf("cells")).toString();
        mapData.monsters        = result.value(rows.indexOf("monsters")).toString();
        mapData.capabilities    = (quint16)result.value(rows.indexOf("capabilities")).toUInt();
        mapData.pos             = result.value(rows.indexOf("mappos")).toString();
        mapData.numgroup       = (quint8)result.value(rows.indexOf("numgroup")).toUInt();
        mapData.groupmaxsize    = (quint8)result.value(rows.indexOf("groupmaxsize")).toUInt();

        m_mapsDataList.insert(mapId, mapData);
    }

    Log::Write(LOG_TYPE_NORMAL, "MapMgr: loaded %u maps data in %s sec.", m_mapsDataList.count(), QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());
    return true;
}

Map* MapMgr::LoadMap(quint16 mapId)
{
    if (!IsMapLoaded(mapId))
    {
        if (!HasMapData(mapId))
        {
            Log::Write(LOG_TYPE_NORMAL, "MapMgr: Map data not found for map %u !", mapId);
            return NULL;
        }

        Map* map = new Map();
        map->Load(m_mapsDataList.value(mapId));
        m_mapsList.insert(mapId, map);
    }

    return m_mapsList.value(mapId);
}

void MapMgr::UnloadMap(quint16 mapId)
{
    if (IsMapLoaded(mapId))
        delete m_mapsList.take(mapId);
}
