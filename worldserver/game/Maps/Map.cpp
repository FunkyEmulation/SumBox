#include "Map.h"

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

}
