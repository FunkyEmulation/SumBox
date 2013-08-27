#include "Map.h"

Map::Map()
{
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
    m_data.date         = mapData.date;
    m_data.width        = mapData.width;
    m_data.height       = mapData.height;
    m_data.places       = mapData.places;
    m_data.key          = mapData.key;
    m_data.data         = mapData.data;
    m_data.cells        = mapData.cells;
    m_data.monsters     = mapData.monsters;
    m_data.capabilities = mapData.capabilities;
    m_data.pos          = mapData.pos;
    m_data.numgroup     = mapData.numgroup;
    m_data.groupmaxsize = mapData.groupmaxsize;
}

void Map::Unload()
{

}
