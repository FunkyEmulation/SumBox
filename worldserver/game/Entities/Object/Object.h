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
    MOVEMENT_UPDATE_TYPE_NONE = 0
};

class Unit;
class Character;

class Object
{
public:
    Object();
    ~Object();

    TypeId GetTypeId() { return m_typeId; }

    void SetGuid(quint32 guid) { m_guid = guid; }
    quint32 GetGuid() const { return m_guid; }

    QString GetName() const { return m_name; }
    int GetGfxId() const { return m_gfxId; }
    int GetSize() const { return m_size; }

    Unit* ToUnit() { if (GetTypeId() == TYPEID_UNIT || GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Unit*>(this); else return NULL; }
    Character* ToCharacter() { if (GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Character*>(this); else return NULL; }

    void BuildMovementUpdate(WorldPacket* data, const MovementUpdateType& movementUpdateType);

protected:
    quint32 m_guid;
    TypeId m_typeId;
    QString m_name;
    int m_gfxId;
    int m_size;
};

#endif // OBJECT_H
