#ifndef UNIT_H
#define UNIT_H

#include "game/Entities/Object/Object.h"

/*
 * Unité : monstres & joueurs
 */

class Unit : public Object
{
public:
    // Getters
    int GetLevel() const { return m_level; }

protected:
    int m_level;

};

#endif // UNIT_H
