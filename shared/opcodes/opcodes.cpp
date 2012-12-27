#include "opcodes.h"

OpcodeStruct opcodeTable[NUM_MSG_TYPES] =
{
    { "SMSG_HELLO_CONNECTION_SERVER", "HC", &WorldSession::HandleServerSide },
    { "SMSG_HELLO_GAME_SERVER", "HG", &WorldSession::HandleServerSide },
    { "SMSG_BAD_VERSION", "AlEv", &WorldSession::HandleServerSide },
    { "SMSG_LOGIN_ERROR", "AlEf", &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_BANNED", "AlEb", &WorldSession::HandleServerSide },
    { "SMSG_ALREADY_LOGGED", "AlEc", &WorldSession::HandleServerSide },

    { "SMSG_GIVE_PSEUDO", "Ad", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_COMMUNAUTY", "Ac", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_SERVERS", "AH", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_GMLEVEL", "AlK", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_QUESTION", "AQ", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_PERSOS", "AxK", &WorldSession::HandleServerSide },
    { "SMSG_SERVER_INFOS", "AYK", &WorldSession::HandleServerSide },
    { "SMSG_RANDOM_PSEUDO", "AP", &WorldSession::HandleServerSide },

    // Packets received before client authentication
    { "CMSG_QUEUE_POSITION", "Af", &WorldSession::HandleBeforeAuth },
};
