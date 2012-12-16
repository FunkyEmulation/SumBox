#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>
#include "../worldserver/game/server/worldsession.h"

enum Opcodes
{
    SMSG_HELLO_CONNECTION_SERVER = 0,
    SMSG_HELLO_GAME_SERVER = 1,
    CMSG_QUEUE_POSITION = 2,
    NUM_MSG_TYPES = 3
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
