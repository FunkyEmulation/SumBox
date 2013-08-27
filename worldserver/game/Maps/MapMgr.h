#ifndef MAPMGR_H
#define MAPMGR_H

#include <QtCore>
#include "databases/database.h"
#include "game/Entities/Character/Character.h"
#include "utils/singleton.h"

// I don't know if we need all table fields
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

typedef QMap<quint16, sMapData> MapsList;

class MapMgr : public Singleton<MapMgr>
{
public:
    MapMgr();
    ~MapMgr();

    bool LoadFromDB();

private:
    MapsList m_mapsList;
};

#endif // MAPMGR_H
