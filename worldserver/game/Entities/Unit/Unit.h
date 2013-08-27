#ifndef UNIT_H
#define UNIT_H

#include "game/Entities/Object/Object.h"
#include "game/Maps/Map.h"

/*
 * Unité : monstres & joueurs
 */

class Unit : public Object
{
public:
    // Getters
    int GetLevel() const      { return m_level; }
    Map* GetMap() const       { return m_map; }
    quint16 GetCellId() const { return m_cellId; }

protected:
    int m_level;
    Map* m_map;
    quint16 m_cellId;

};

#endif // UNIT_H
