#include "Character.h"
#include "utils/util.h"

Character::Character(WorldSession* session) : Unit()
{
    m_session = session;

    SetGuid(0);
    m_name = QString();
    m_race = 0;
    m_gender = 0;
    m_gfxId = 0;
    m_color1 = 0;
    m_color2 = 0;
    m_color3 = 0;
}

Character::~Character()
{

}

bool Character::Create(quint32 guid, sCharacterCreateInfos characterCreateInfos)
{
    SetGuid(guid);

    m_name      = characterCreateInfos.name;
    m_race      = characterCreateInfos.race;
    m_gender    = characterCreateInfos.gender;
    m_gfxId     = characterCreateInfos.gfxId;
    m_color1    = characterCreateInfos.color1;
    m_color2    = characterCreateInfos.color2;
    m_color3    = characterCreateInfos.color3;

    return true;
}

bool Character::LoadFromDB()
{
    return true;
}

void Character::SaveToDB(bool create)
{
    if (create)
    {
        Database::Char()->PQuery(INSERT_CHARACTER, GetGuid(), GetSession()->GetAccountInfos().id, m_name.toLatin1().data(), m_race, m_gender, m_gfxId, m_color1, m_color2, m_color3);
        Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, GetSession()->GetAccountInfos().id, ConfigMgr::Instance()->World()->GetInt("ServerId"), GetSession()->GetCharsCount() + 1);
    }
    else
    {
        // Todo update player
    }
}
