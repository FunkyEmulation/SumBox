#include "Server/WorldSession.h"

void WorldSession::HandleChatMessage(QString& packet)
{
    QString message = packet.mid(4);
    message.remove(message.length() - 1, 1);

    WorldPacket data(SMSG_CHAT_MESSAGE);
    data << message;
    SendPacket(data);

    WorldPacket data2(MSG_UNKNOWN_OPCODE);
    data2 << "cMK|" << GetCharacter()->GetGuid() << "|";
    data2 << GetCharacter()->GetName() << "|";
    data2 << message << "|";
    SendPacket(data2);
}

// Parler dans le chat :
// Game: Recv << BM*|hello|
// Game: Map: Send>>cMK|3|mjcnf|hello|

// Smiley :
// Game: Recv << BS1
// Game: Map: Send>>cS3|1

// Emote assis :
// Game: Recv << eU1
// Game: Send>>ILS1000
// Set Emote 1
// Is sitted true
// Game: Map: Send>>eUK3|1

// Autres Emote :
// Game: Recv << eU2
// Set Emote 2
// Is sitted false
// Game: Map: Send>>eUK3|2
