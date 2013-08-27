#include "MapMgr.h"

template<> MapMgr*  Singleton<MapMgr>::m_instance = 0;

MapMgr::MapMgr()
{
    m_mapsList.clear();
}

MapMgr::~MapMgr()
{
    m_mapsList.clear();
}

bool MapMgr::LoadFromDB()
{
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

        m_mapsList.insert(mapId, mapData);
    }

    Log::Write(LOG_TYPE_NORMAL, "MapMgr: loaded %u maps data in %s sec.", m_mapsList.count(), QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());
    return true;
}
