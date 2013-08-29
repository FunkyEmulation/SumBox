#include "Object.h"

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

void Object::BuildMovementUpdate(WorldPacket *data, const MovementUpdateType &movementUpdateType)
{
    // TODO
}
