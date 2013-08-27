#include "opcodes.h"
#include "game/server/worldsession.h"

OpcodeStruct opcodeTable[NUM_MSG_TYPES] =
{
    {"MSG_UNKNOWN_OPCODE",                          "",         &WorldSession::HandleNULL },

    // Client messages (CMSG)
    { "CMSG_CHAR_CREATE",                           "AA",       &WorldSession::HandleCharCreate },
    { "CMSG_CHAR_DELETE",                           "AD",       &WorldSession::HandleCharDelete },
    { "CMSG_CHAR_LIST",                             "AL",       &WorldSession::HandleCharList },
    { "CMSG_GAME_CREATE",                           "GC",       &WorldSession::HandleGameCreate },
    { "CMSG_GIFTS_LIST",                            "Ag",       &WorldSession::HandleGiftsList },
    { "CMSG_SCREEN_INFO",                           "Ir",       &WorldSession::HandleScreenInfo },
    { "CMSG_SESSION_KEY",                           "Ai",       &WorldSession::HandleSessionKey },
    { "CMSG_TICKET",                                "AT",       &WorldSession::HandleTicket },

    // Server messages (SMSG)
    { "SMSG_ACCOUNT_ALREADY_CONNECTED",             "AlEc",     &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_BAD_CLIENT_VERSION",            "ALEv",     &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_BANNED",                        "AlEb",     &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_GMLEVEL",                       "AlK",      &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_LOGIN_ERROR",                   "AlEf",     &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_PSEUDO",                        "Ad",       &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_REALM_CHAR",                    "AxK",      &WorldSession::HandleServerSide },
    { "SMSG_ACCOUNT_SECRET_QUESTION",               "AQ",       &WorldSession::HandleServerSide },
    { "SMSG_CHAR_LIST",                             "AL|",      &WorldSession::HandleServerSide },
    { "SMSG_CHAR_CREATE",                           "AA|",      &WorldSession::HandleServerSide },
    { "SMSG_CHAR_CREATE_ERROR",                     "AAE",      &WorldSession::HandleServerSide },
    { "SMSG_CHAR_DELETE",                           "ADE",      &WorldSession::HandleServerSide },
    { "SMSG_CHAR_STATS",                            "As",       &WorldSession::HandleServerSide },
    { "SMSG_GAME_CREATE",                           "GCK|",     &WorldSession::HandleServerSide },
    { "SMSG_GIFTS_LIST",                            "Ag1",      &WorldSession::HandleServerSide },
    { "SMSG_COMMUNITY",                             "Ac",       &WorldSession::HandleServerSide },
    { "SMSG_HELLO_CONNECTION_SERVER",               "HC",       &WorldSession::HandleServerSide },
    { "SMSG_HELLO_GAME_SERVER",                     "HG",       &WorldSession::HandleServerSide },
    { "SMSG_MAP_DATA",                              "GDM|",     &WorldSession::HandleServerSide },
    { "SMSG_QUEUE_OUT_OF_BOUNDS",                   "M116",     &WorldSession::HandleServerSide },
    { "SMSG_REALM_INFOS",                           "AYK",      &WorldSession::HandleServerSide },
    { "SMSG_REALMS_LIST",                           "AH",       &WorldSession::HandleServerSide },
    { "SMSG_SEARCH_FRIEND",                         "AF",       &WorldSession::HandleServerSide },
    { "SMSG_TICKET_ACCEPTED",                       "ATK0",     &WorldSession::HandleServerSide },
    { "SMSG_TICKET_REFUSED",                        "ATE",      &WorldSession::HandleServerSide },

    // Client and server messages (MSG)
    { "MSG_CHAR_RANDOM_NAME",                       "AP",       &WorldSession::HandleCharRandomPseudo },
    { "MSG_CHAR_SELECT",                            "AS",       &WorldSession::HandleCharSelect },
    { "MSG_QUEUE_POSITION",                         "Af",       &WorldSession::HandleQueuePosition },
    { "MSG_REGIONAL_VERSION",                       "AV",       &WorldSession::HandleRegionalVersion },
};
