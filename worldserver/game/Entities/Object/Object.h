#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "packets/worldpacket.h"

enum TypeId
{
    TYPEID_OBJECT = 0,
    TYPEID_UNIT = 3,
    TYPEID_CHARACTER = 2
};

enum MovementUpdateType
{
    MOVEMENT_UPDATE_TYPE_NONE       = 0,
    MOVEMENT_UPDATE_TYPE_ADD,
    MOVEMENT_UPDATE_TYPE_UPDATE,
    MOVEMENT_UPDATE_TYPE_REMOVE
};

enum SpriteType
{
    SPRITE_TYPE_NONE                = 0,
    SPRITE_TYPE_MONSTER             = -1,
    SPRITE_TYPE_CREATURE            = -2,
    SPRITE_TYPE_MONSTER_GROUP       = -3,
    SPRITE_TYPE_NPC                 = -4, // ?
    SPRITE_TYPE_OFFLINE_CHARACTER   = -5,
    SPRITE_TYPE_TAX_COLLECTOR       = -6,
    SPRITE_TYPE_MUTANT              = -7,
    SPRITE_TYPE_CHARACTER_MUTANT    = -8, // ?
    SPRITE_TYPE_PARK_MOUNT          = -9,
    SPRITE_TYPE_PRISM               = -10
};

class Unit;
class Character;

class Object
{
public:
    Object();
    ~Object();

    TypeId GetTypeId() { return m_typeId; }

    void SetValue(quint16 index, QVariant value);
    QVariant GetValue(quint16 index) { return m_values[index]; }

    void SetGuid(quint32 guid) { m_guid = guid; }
    quint32 GetGuid() const { return m_guid; }

    QString GetName() const { return m_name; }
    int GetGfxId() const { return m_gfxId; }
    int GetSize() const { return m_size; }

    Unit* ToUnit() { if (GetTypeId() == TYPEID_UNIT || GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Unit*>(this); else return NULL; }
    Character* ToCharacter() { if (GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Character*>(this); else return NULL; }

    void BuildMovementUpdate(WorldPacket* data, const MovementUpdateType& movementUpdateType);

protected:
    QMap<quint16, QVariant> m_values;

    quint32 m_guid;
    TypeId m_typeId;
    QString m_name;
    int m_gfxId;
    int m_size;
};

#endif // OBJECT_H
