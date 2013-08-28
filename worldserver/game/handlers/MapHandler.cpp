#include "game/server/worldsession.h"

void WorldSession::SendMapData(const sMapData& mapData)
{
    WorldPacket data(SMSG_MAP_DATA);
    data << mapData.id;
    data << "|" << mapData.date;
    data << "|" << mapData.key;
    SendPacket(data);
}

// GDM|7411|0612131401|
