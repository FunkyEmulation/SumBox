#include "game/server/worldsession.h"

void WorldSession::HandleGameCreate(QString& packet)
{
    quint8 gameType = (quint8)packet.mid(2).toUInt();

    Character* character = GetCharacter();
    if (!character)
        return;

    WorldPacket data(SMSG_GAME_CREATE);
    data << gameType << "|";
    data << character->GetName();
    SendPacket(data);

    // Then send character stats
    // Todo : check packet struct in client : this.aks.Account.onStats(sData.substr(2));

    // Then send map data
    // Todo : check packet struct in client : this.aks.Game.onMapData(sData.substr(4));
    SendMapData(/*mapId, mapDate, mapKey*/);
}
