#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "Packets/WorldPacket.h"

enum TypeId
{
    TYPEID_OBJECT              = 0,
    TYPEID_CHARACTER           = 1,
    TYPEID_UNIT                = 2, // temp

    TYPEID_MONSTER             = -1,
    TYPEID_CREATURE            = -2,
    TYPEID_MONSTER_GROUP       = -3,
    TYPEID_NPC                 = -4, // ?
    TYPEID_OFFLINE_CHARACTER   = -5,
    TYPEID_TAX_COLLECTOR       = -6,
    TYPEID_MUTANT              = -7,
    TYPEID_CHARACTER_MUTANT    = -8, // ?
    TYPEID_PARK_MOUNT          = -9,
    TYPEID_PRISM               = -10
};

enum MovementUpdateType
{
    MOVEMENT_UPDATE_TYPE_NONE,
    MOVEMENT_UPDATE_TYPE_ADD,
    MOVEMENT_UPDATE_TYPE_UPDATE,
    MOVEMENT_UPDATE_TYPE_REMOVE
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

    void SetMapId(quint16 mapId) { m_mapId = mapId; }
    quint16 GetMapId() const { return m_mapId; }

    void SetCellId(quint16 cellId) { m_cellId = cellId; }
    quint16 GetCellId() const { return m_cellId; }

    quint8 GetOrientation() { return m_orientation; }

    Character* ToCharacter() { if (GetTypeId() == TYPEID_CHARACTER) return reinterpret_cast<Character*>(this); else return NULL; }

    void BuildMovementUpdate(WorldPacket* data, const MovementUpdateType& movementUpdateType);

protected:
    QMap<quint16, QVariant> m_values;

    quint32 m_guid;
    TypeId m_typeId;
    QString m_name;
    quint16 m_gfxId;
    quint16 m_size;
	
    quint16 m_mapId;
	quint16 m_cellId;
    quint8 m_orientation;
};

#endif // OBJECT_H
