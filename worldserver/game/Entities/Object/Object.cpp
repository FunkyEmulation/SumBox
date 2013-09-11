#include "Object.h"
#include "game/Entities/Character/Character.h"

Object::Object()
{
    m_guid      = 0;
    m_typeId    = TYPEID_OBJECT;
    m_name      = QString();
    m_gfxId     = 0;
    m_size      = 0;
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

        //*data << GetRace() << ","; // (SpriteType == race ?) du coup ça doit etre dans la classe character ?
        *data << -1 << ",";

        *data << 0 << "*" << 0 << ";"; // titreId * params

        *data << GetGfxId() << "^" << GetSize() << ";";
        //data << GetGender() << ";";

        SpriteType spriteType = SPRITE_TYPE_NONE;
        switch (spriteType)
        {
        case SPRITE_TYPE_MONSTER:
        case SPRITE_TYPE_CREATURE:
            Character* character = this->ToCharacter();

            *data << character->GetLevel() << ";"; // powerlevel - quelle différence entre powerlevel et level ?
            *data << character->GetColor1() << ";"; // en hexa
            *data << character->GetColor2() << ";"; // en hexa
            *data << character->GetColor3() << ";"; // en hexa
            *data << 0 << ";"; // accessories

            // Si fight
            {
            *data << 0 << ";"; // LP
            *data << 0 << ";"; // AP
            *data << 0 << ";"; // MP

            // resistances (seulement si condition ?)
            *data << 0 << ";"; // resistance 1
            *data << 0 << ";"; // resistance 2
            *data << 0 << ";"; // resistance 3
            *data << 0 << ";"; // resistance 4
            *data << 0 << ";"; // resistance 5
            *data << 0 << ";"; // resistance 6
            *data << 0 << ";"; // resistance 7

            *data << 0 << ";"; // team

            }
            break;

        /*case SPRITE_TYPE_MONSTER_GROUP: break;
        case SPRITE_TYPE_NPC:
            //*data << GetGender() << ";"; // gender
            break;
        case SPRITE_TYPE_OFFLINE_CHARACTER: break;
        case SPRITE_TYPE_TAX_COLLECTOR: break;
        case SPRITE_TYPE_MUTANT: break;
        case SPRITE_TYPE_CHARACTER_MUTANT: break;
        case SPRITE_TYPE_PARK_MOUNT: break;
        case SPRITE_TYPE_PRISM: break;*/
        }
    }
    else
        *data << GetGuid();
}
