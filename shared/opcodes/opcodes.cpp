#include "opcodes.h"

OpcodeHandler opcodeTable[NUM_MSG_TYPES] =
{
    { "SMSG_HELLO_CONNECTION_SERVER", "HC" },
    { "SMSG_HELLO_GAME_SERVER", "HG" }
};

QString GetOpcodeName(quint8 opcode)
{
    if(opcode >= 3)
        return "Unknown opcode";

    return opcodeTable[opcode].name;
}
