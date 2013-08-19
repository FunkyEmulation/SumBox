#include "opcodes.h"

OpcodeStruct opcodeTable[NUM_MSG_TYPES] =
{
    {"MSG_UNKNOWN_OPCODE", "", &WorldSession::HandleNULL },

    { "SMSG_HELLO_CONNECTION_SERVER", "HC", &WorldSession::HandleServerSide },
    { "SMSG_HELLO_GAME_SERVER", "HG", &WorldSession::HandleServerSide },
    { "SMSG_BAD_VERSION", "AlEv", &WorldSession::HandleServerSide },
    { "SMSG_LOGIN_ERROR", "AlEf", &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_BANNED", "AlEb", &WorldSession::HandleServerSide },
    { "SMSG_ALREADY_LOGGED", "AlEc", &WorldSession::HandleServerSide },
    { "SMSG_QUEUE_OUT_OF_BOUNDS", "M116", &WorldSession::HandleServerSide },
    { "SMSG_DISCONNECT", "HD", &WorldSession::HandleServerSide },

    { "SMSG_GIVE_PSEUDO", "Ad", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_COMMUNAUTY", "Ac", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_SERVERS", "AH", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_GMLEVEL", "AlK", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_QUESTION", "AQ", &WorldSession::HandleServerSide },
    { "SMSG_GIVE_PERSOS", "AxK", &WorldSession::HandleServerSide },
    { "SMSG_SERVER_INFOS", "AYK", &WorldSession::HandleServerSide },
    { "SMSG_SEARCH_FRIEND", "AF", &WorldSession::HandleServerSide },

    // Packets received before client authentication
    { "MSG_QUEUE_POSITION", "Af", &WorldSession::HandleQueuePosition },

    // Packets received after client authentication
    { "CMSG_TICKET_RESPONSE", "AT", &WorldSession::HandleTicketResponse },
    { "SMSG_TICKET_REFUSED", "ATE", &WorldSession::HandleServerSide },
    { "SMSG_TICKET_ACCEPTED", "ATK0", &WorldSession::HandleServerSide },
    { "MSG_REGIONAL_VERSION", "AV", &WorldSession::HandleRegionalVersion },
    { "CMSG_REQUEST_GIFTS", "Ag", &WorldSession::HandleListGifts },
    { "SMSG_LIST_GIFTS", "Ag1", &WorldSession::HandleServerSide },
    { "CMSG_GIVE_KEY", "Ai", &WorldSession::HandleKey },
    { "CMSG_REQUEST_CHARS", "AL", &WorldSession::HandleCharactersList },
    { "SMSG_CHARACTER_LIST", "AL|", &WorldSession::HandleSendCharacterList },
    { "CMSG_RANDOM_PSEUDO", "AP", &WorldSession::HandleRandomPseudo },
    { "CMSG_CREATE_CHAR", "AA", &WorldSession::HandleCreatePerso },
    { "SMSG_CREATE_CHAR_OK", "AA|", &WorldSession::HandleServerSide },
    { "SMSG_CREATE_CHAR_ERROR", "AAE", &WorldSession::HandleServerSide },
    { "CMSG_DELETE_CHAR", "AD", &WorldSession::HandleDeleteChar },
    { "SMSG_DELETE_CHAR_ERROR", "ADE", &WorldSession::HandleServerSide },
    { "CMSG_SELECT_CHAR", "AS", &WorldSession::HandleSelectChar }
};
