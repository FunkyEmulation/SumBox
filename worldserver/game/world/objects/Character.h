#ifndef CHARACTER_H
#define CHARACTER_H

#include "LivingBeing.h"

class Account;
class ObjectFactory;

class Character : public LivingBeing
{
public:
    // Getters
    Account* GetAccount() const { return m_account; }
    int GetBreedId() const { return m_breed; }

private:
    inline Character(int id, QString name, int gender, int gfxId, int color1, int color2, int color3, int size, int level, int breed)
    {
        m_id = id;
        m_name = name;
        m_gender = gender;
        m_gfxId = gfxId;
        m_color1 = color1;
        m_color2 = color2;
        m_color3 = color3;
        m_size = size;
        m_level = level;
        m_breed = breed;
    }
    Account* m_account;
    int m_breed;

    friend class ObjectFactory;
};

#endif // CHARACTER_H
