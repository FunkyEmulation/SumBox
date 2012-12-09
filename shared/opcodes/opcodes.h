#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

enum Opcodes
{
    SMSG_HELLO_CONNECTION_SERVER = 1,
    SMSG_HELLO_GAME_SERVER = 2,
    NUM_MSG_TYPES = 3
};

struct OpcodeHandler
{
    QString name;
    QString header;
};

#endif
