#include "Server/WorldSession.h"

void WorldSession::SendMapData(const sMapData& mapData)
{
    WorldPacket data(SMSG_MAP_DATA);
    data << mapData.id;
    data << "|" << mapData.date;
    data << "|" << mapData.key;
    SendPacket(data);
}
