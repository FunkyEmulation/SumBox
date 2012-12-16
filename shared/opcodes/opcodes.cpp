#include "opcodes.h"

OpcodeStruct opcodeTable[NUM_MSG_TYPES] =
{
    { "SMSG_HELLO_CONNECTION_SERVER", "HC", &WorldSession::HandleServerSide },
    { "SMSG_HELLO_GAME_SERVER", "HG", &WorldSession::HandleServerSide },

    // Packets received before client authentication
    { "CMSG_QUEUE_POSITION", "Af", &WorldSession::HandleBeforeAuth },
};
