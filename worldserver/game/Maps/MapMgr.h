#ifndef MAPMGR_H
#define MAPMGR_H

#include <QtCore>
#include "databases/database.h"
#include "utils/singleton.h"

struct sMapData
{
    QString date;
    quint8 width;
    quint8 height;
    QString places;
    QString key;
    QString data;
    QString cells;
    QString monsters;
    quint16 capabilities;
    QString pos;
    quint8 numgroup;
    quint8 groupmaxsize;
};

#include "Map.h"

class Map;

typedef QMap<quint16, sMapData> MapsDataList;
typedef QMap<quint16, Map*> MapsList;

class MapMgr : public Singleton<MapMgr>
{
public:
    MapMgr();
    ~MapMgr();

    bool LoadFromDB();

    bool HasMapData(quint16 mapId)
    {
        return m_mapsDataList.contains(mapId);
    }

    bool IsMapLoaded(quint16 mapId)
    {
        return m_mapsList.contains(mapId);
    }

    Map* LoadMap(quint16 mapId);
    void UnloadMap(quint16 mapId);

private:
    MapsDataList m_mapsDataList;
    MapsList m_mapsList;
};

#endif // MAPMGR_H
