#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>
#include "../worldserver/game/server/worldsession.h"

class WorldSession;

enum Opcodes
{
    MSG_UNKNOWN_OPCODE = 0,

    SMSG_HELLO_CONNECTION_SERVER = 1,
    SMSG_HELLO_GAME_SERVER = 2,
    SMSG_BAD_VERSION = 3,
    SMSG_LOGIN_ERROR = 4,
    SMSG_ACCOUNT_BANNED = 5,
    SMSG_ALREADY_LOGGED = 6,
    SMSG_QUEUE_OUT_OF_BOUNDS = 7,
    SMSG_DISCONNECT = 8,

    SMSG_GIVE_PSEUDO = 9,
    SMSG_GIVE_COMMUNAUTY = 10,
    SMSG_GIVE_SERVERS = 11,
    SMSG_GIVE_GMLEVEL = 12,
    SMSG_GIVE_QUESTION = 13,
    SMSG_GIVE_PERSOS = 14,
    SMSG_SERVER_INFOS = 15,
    SMSG_RANDOM_PSEUDO = 16,

    CMSG_QUEUE_POSITION = 17,
    CMSG_TICKET_RESPONSE = 18,
    SMSG_TICKET_REFUSED = 19,
    SMSG_TICKET_ACCEPTED = 20,
    CMSG_REGIONAL_VERSION = 21,
    SMSG_REGIONAL_VERSION = 22,
    CMSG_REQUEST_GIFTS = 23,
    SMSG_LIST_GIFTS = 24,
    CMSG_GIVE_KEY = 25,
    CMSG_REQUEST_CHARS = 26,
    SMSG_SEND_CHARS = 27,
    NUM_MSG_TYPES = 28
};

struct OpcodeStruct
{
    QString name;
    QString header;
    void (WorldSession::*handler)(QString& packet);
};

extern OpcodeStruct opcodeTable[NUM_MSG_TYPES];

inline QString GetOpcodeName(quint8 opcode)
{
    if(opcode >= NUM_MSG_TYPES)
        return "Unknown opcode";

    return opcodeTable[opcode].name;
}

inline QString GetOpcodeHeader(quint8 opcode)
{
    if(opcode >= NUM_MSG_TYPES)
        return "Unknown opcode";

    return opcodeTable[opcode].header;
}

// tmp
inline OpcodeStruct GetOpcodeByHeader(QString header)
{
    for (quint8 i = 0; i < NUM_MSG_TYPES; ++i)
        if (header == opcodeTable[i].header)
            return opcodeTable[i];

    return opcodeTable[MSG_UNKNOWN_OPCODE];
}

#endif
