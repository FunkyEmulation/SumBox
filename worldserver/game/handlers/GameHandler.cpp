#include "Server/WorldSession.h"
#include "Utils/Util.h"

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
    WorldPacket data(SMSG_OBJECT_MOVEMENT);
    GetCharacter()->BuildMovementUpdate(&data, MOVEMENT_UPDATE_TYPE_ADD);
    SendPacket(data);

    SendPacket(WorldPacket(SMSG_MAP_LOADED));
}

void WorldSession::HandleGameAction(QString& packet)
{
    quint16 actionId = (quint16)packet.mid(2, 3).toUShort();
    WorldPacket data(MSG_GAME_ACTION);

    switch (actionId)
    {
    case 1:
    {
        data << "0;1;";
        data << GetCharacter()->GetGuid() << ";";
        data << "a" << Utils::GetCellString(GetCharacter()->GetCellId()) << packet.mid(5);
        SendPacket(data);

        // No idea if it's correct !
        GetCharacter()->SetCellId(Utils::GetCellId(packet.mid(packet.length() - 2)));
    } break;
    default:
        break;
    }
}

void WorldSession::HandleGameActionFinished(QString& /*packet*/)
{
    //bool actionSuccess = packet.mid(2, 1) == "K";
    // quint8 actionId = packet.mid(3);
    // Todo : mettre en place le système d'actions

    // Don't know if correct
    GetCharacter()->GetMap()->MoveToCell(GetCharacter()->GetCellId());

    SendPacket(WorldPacket(SMSG_BASIC_NOTHING));
}
