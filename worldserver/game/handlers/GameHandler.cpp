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
    WorldPacket data(SMSG_OBJECT_MOVEMENT);
    GetCharacter()->BuildMovementUpdate(&data, MOVEMENT_UPDATE_TYPE_ADD);
    SendPacket(data);

    SendPacket(WorldPacket(SMSG_MAP_LOADED));
}

void WorldSession::HandleGameAction(QString& packet)
{
    quint16 actionId = (quint16)packet.mid(2, 3).toUShort();

    switch (actionId)
    {
    case 1:
    {
        // SocketManager.GAME_SEND_GA_PACKET_TO_MAP(_perso.get_curCarte(), ""+GA._id, 1, _perso.get_GUID()+"", "a"+CryptManager.cellID_To_Code(_perso.get_curCell().getID())+path);
        // String packet = "GA"+gameActionID+";"+actionID+";"+s1; if(!s2.equals(""))packet += ";"+s2;
        WorldPacket data(MSG_GAME_ACTION);
        data << "0;1;-1;acWdc-fcG";
        SendPacket(data);
    } break;
    default:
        break;
    }
}
