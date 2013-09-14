#include "Map.h"
#include "Entities/Character/Character.h"

Map::Map()
{
    m_data.id           = 0;
    m_data.date         = QString();
    m_data.width        = 0;
    m_data.height       = 0;
    m_data.places       = QString();
    m_data.key          = QString();
    m_data.data         = QString();
    m_data.cells        = QString();
    m_data.monsters     = QString();
    m_data.capabilities = 0;
    m_data.pos          = QString();
    m_data.numgroup     = 0;
    m_data.groupmaxsize = 0;

    m_objectsList.clear();
}

Map::~Map()
{
    Unload();
}

void Map::Load(const sMapData& mapData)
{
    m_data = mapData;
}

void Map::Unload()
{
    m_objectsList.clear();
}

void Map::AddToMap(Object* object)
{
    m_objectsList.push_back(object);

    // Don't know if we can add only player on map or not
    Character* character = object->ToCharacter();
    if (!character) return;

    WorldPacket data(SMSG_OBJECT_MOVEMENT);
    object->BuildMovementUpdate(&data, MOVEMENT_UPDATE_TYPE_ADD);
    character->GetSession()->SendPacket(data);
}

void Map::SendPacket(const WorldPacket &data)
{
    for (ObjectsList::ConstIterator itr = m_objectsList.begin(); itr != m_objectsList.end(); ++itr)
        if ((*itr) && (*itr)->ToCharacter())
            (*itr)->ToCharacter()->GetSession()->SendPacket(data);
}
