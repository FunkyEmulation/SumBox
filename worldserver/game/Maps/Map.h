#ifndef MAP_H
#define MAP_H

#include <QtCore>
#include "MapMgr.h"

class Map
{
public:
    Map();
    ~Map();

    void Load(const sMapData& mapData);
    void Unload();

    const sMapData& GetData() { return m_data; }

private:
    sMapData m_data;
};

#endif // MAP_H
