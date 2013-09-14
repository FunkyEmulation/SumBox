#ifndef UNIT_H
#define UNIT_H

#include "Entities/Object/Object.h"
#include "Maps/Map.h"

class Map;

class Unit : public Object
{
public:
    Unit();
    ~Unit();

    // Getters
    int GetLevel() const      { return m_level; }
    Map* GetMap() const       { return m_map; }

protected:
    quint16 m_level;
    Map* m_map;
};

#endif // UNIT_H
