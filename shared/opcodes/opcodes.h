#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

enum Opcodes
{
    SMSG_HELLO_CONNECTION_SERVER = 1,
    SMSG_HELLO_GAME_SERVER = 2,
    NUM_MSG_TYPES = 3
};

struct OpcodeStruct
{
    QString name;
    QString header;
};

extern OpcodeStruct opcodeTable[NUM_MSG_TYPES];

inline QString GetOpcodeName(quint8 opcode)
{
    if(opcode >= 3)
        return "Unknown opcode";

    return opcodeTable[opcode].name;
}

inline QString GetOpcodeHeader(quint8 opcode)
{
    if(opcode >= 3)
        return "Unknown opcode";

    return opcodeTable[opcode].header;
}

#endif
