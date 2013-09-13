#include "Object.h"
#include "Entities/Character/Character.h"

Object::Object()
{
    m_guid          = 0;
    m_typeId        = TYPEID_OBJECT;
    m_name          = QString();
    m_gfxId         = 0;
    m_size          = 100;
}

Object::~Object()
{

}

void Object::SetValue(quint16 index, QVariant value)
{
    if (m_values[index] != value)
        m_values[index] = value;
}

void Object::BuildMovementUpdate(WorldPacket *data, const MovementUpdateType &movementUpdateType)
{
    switch (movementUpdateType)
    {
    case MOVEMENT_UPDATE_TYPE_ADD:      *data << "+"; break;
    case MOVEMENT_UPDATE_TYPE_UPDATE:   *data << "~"; break;
    case MOVEMENT_UPDATE_TYPE_REMOVE:   *data << "-"; break;
    default: return;
    }

    if (movementUpdateType != MOVEMENT_UPDATE_TYPE_REMOVE)
    {
        *data << 0 << ";"; // cellID
        *data << 0 << ";"; // orientation
        *data << 0 << ";"; // mobgroupbonusvalues
        *data << GetGuid() << ";";
        *data << GetName() << ";";

        Character* character = NULL; // faire différement car utilie de la mémoire
        if (GetTypeId() == TYPEID_CHARACTER)
        {
            character = ToCharacter();
            if (!character)
                return;

            *data << character->GetRace() << ",";
        }
        else
            *data << GetTypeId() << ",";

        *data << 0 << "*" << 0 << ";"; // titreId * params
        *data << GetGfxId() << "^" << GetSize() << ";";

        switch (GetTypeId())
        {
        case TYPEID_CHARACTER:

            *data << character->GetGender() << ";";

            /*
            IF FIGHT
            {
            *data << character->GetLevel() << ";";
            *data << 0 << ";"; // var _loc51 = _loc10[9]; ??
            *data << character->GetColor1() << ";";
            *data << character->GetColor2() << ";";
            *data << character->GetColor3() << ";";
            *data << 0 << ";"; // accessories
            *data << 0 << ";"; // LP
            *data << 0 << ";"; // AP
            *data << 0 << ";"; // MP
            *data << "0;0;0;0;0;0;0;"; // resistances
            *data << 0; // team

            TODO MOUNT
            _loc10[25] => mount
            }
            ELSE
            */

            *data << "0,0,"; // alignment ?
            *data << "0,"; // rank
            *data << (GetLevel() + GetGuid()) << ";";
            *data << character->GetColor1() << ";";
            *data << character->GetColor2() << ";";
            *data << character->GetColor3() << ";";
            *data << 0 << ";"; // accessories
            *data << 0 << ";"; // aura
            *data << 0 << ";"; // emote
            *data << 0 << ";"; // emoteTimer
            *data << 0 << ";"; // guildName
            *data << 0 << ";"; // emblem
            *data << 0 << ";"; // restrictions

            // TODO MOUNT
            *data << 0 << ";";

            break;

        /*case TYPEID_MONSTER:
        case TYPEID_CREATURE:
            break;

        case TYPEID_MONSTER_GROUP: break;
        case TYPEID_NPC:
            break;
        case TYPEID_OFFLINE_CHARACTER: break;
        case TYPEID_TAX_COLLECTOR: break;
        case TYPEID_MUTANT: break;
        case TYPEID_CHARACTER_MUTANT: break;
        case TYPEID_PARK_MOUNT: break;
        case TYPEID_PRISM: break;*/
        }
    }
    else
        *data << GetGuid();
}
