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

    SendMapData();
}

void WorldSession::SendMapData()
{
    if(!GetCharacter() || (GetCharacter() && !GetCharacter()->GetMap()))
        return;

    WorldPacket data(SMSG_MAP_DATA);
    data << GetCharacter()->GetMap()->GetData().id;
    data << "|" << GetCharacter()->GetMap()->GetData().date;
    data << "|" << GetCharacter()->GetMap()->GetData().key;
    SendPacket(data);
}

// GDM|7411|0612131401|
