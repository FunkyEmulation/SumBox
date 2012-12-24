#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>
#include "../worldserver/game/server/worldsession.h"

enum Opcodes
{
    SMSG_HELLO_CONNECTION_SERVER = 0,
    SMSG_HELLO_GAME_SERVER = 1,
    SMSG_BAD_VERSION = 2,
    SMSG_LOGIN_ERROR = 3,
    SMSG_ACCOUNT_BANNED = 4,
    SMSG_ALREADY_LOGGED = 5,

    SMSG_GIVE_PSEUDO = 6,
    SMSG_GIVE_COMMUNAUTY = 7,
    SMSG_GIVE_SERVERS = 8,
    SMSG_GIVE_GMLEVEL = 9,
    SMSG_GIVE_QUESTION = 10,
    SMSG_GIVE_PERSOS = 11,
    SMSG_RANDOM_PSEUDO = 12,

    CMSG_QUEUE_POSITION = 13,
    NUM_MSG_TYPES = 14
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

#endif
