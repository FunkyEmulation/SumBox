#ifndef MAP_H
#define MAP_H

#include <QtCore>

#include "MapMgr.h"
#include "Entities/Object/Object.h"
#include "Packets/WorldPacket.h"

typedef QList<Object*> ObjectsList;

class Map
{
public:
    Map();
    ~Map();

    void Load(const sMapData& mapData);
    void Unload();

    const sMapData& GetData() { return m_data; }

    void AddToMap(Object* object);
    void SendPacket(const WorldPacket& data);

private:
    sMapData m_data;
    ObjectsList m_objectsList;
};

#endif // MAP_H
