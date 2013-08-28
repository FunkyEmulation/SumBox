#ifndef MAP_H
#define MAP_H

#include <QtCore>
#include "MapMgr.h"
#include "game/Entities/Object/Object.h"

typedef QList<Object*> ObjectList;

class Map
{
public:
    Map();
    ~Map();

    void Load(const sMapData& mapData);
    void Unload();

    const sMapData& GetData() { return m_data; }

    void AddToMap(Object* object);

private:
    sMapData m_data;
    ObjectList m_objectList;
};

#endif // MAP_H
