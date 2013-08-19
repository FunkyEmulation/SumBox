#ifndef LIVINGBEING_H
#define LIVINGBEING_H

#include "Being.h"

/*
 * Êtres vivants : monstres & joueurs
 */

class LivingBeing : public Being
{
public:
    // Getters
    int GetLvl() const { return m_level; }

protected:
    int m_level;

};

#endif // LIVINGBEING_H
