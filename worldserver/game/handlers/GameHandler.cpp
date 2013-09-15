#include "Server/WorldSession.h"

void WorldSession::HandleGameCreate(QString& packet)
{
    Character* character = GetCharacter();
    if (!character)
        return;

    quint8 gameType = (quint8)packet.mid(2).toUInt();

    WorldPacket data(SMSG_GAME_CREATE);
    data << gameType << "|";
    data << character->GetName();
    SendPacket(data);

    character->SendCharacterStats();

    Map* map = character->GetMap();
    if (!map)
        return;

    SendMapData(map->GetData());
    map->AddToMap(character);
}

void WorldSession::HandleGameInformations(QString& /*packet*/)
{
    // TODO

    SendPacket(WorldPacket(SMSG_MAP_LOADED));
}
