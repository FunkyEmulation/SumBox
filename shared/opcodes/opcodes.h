#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>
#include "game/server/worldsession.h"

class WorldSession;

enum Opcodes
{
    MSG_UNKNOWN_OPCODE,

    SMSG_HELLO_CONNECTION_SERVER,
    SMSG_HELLO_GAME_SERVER,
    SMSG_BAD_VERSION,
    SMSG_LOGIN_ERROR,
    SMSG_ACCOUNT_BANNED,
    SMSG_ALREADY_LOGGED,
    SMSG_QUEUE_OUT_OF_BOUNDS,
    SMSG_DISCONNECT,

    SMSG_GIVE_PSEUDO,
    SMSG_GIVE_COMMUNAUTY,
    SMSG_GIVE_SERVERS,
    SMSG_GIVE_GMLEVEL,
    SMSG_GIVE_QUESTION,
    SMSG_GIVE_PERSOS,
    SMSG_SERVER_INFOS,
    SMSG_SEARCH_FRIEND,

    CMSG_QUEUE_POSITION,
    SMSG_QUEUE_POSITION,

    CMSG_TICKET_RESPONSE,
    SMSG_TICKET_REFUSED,
    SMSG_TICKET_ACCEPTED,
    MSG_REGIONAL_VERSION,
    CMSG_REQUEST_GIFTS,
    SMSG_LIST_GIFTS,
    CMSG_GIVE_KEY,

    CMSG_REQUEST_CHARS,
    SMSG_CHARACTER_LIST,
    CMSG_RANDOM_PSEUDO,
    CMSG_CREATE_CHAR,
    SMSG_CREATE_CHAR_OK,
    SMSG_CREATE_CHAR_ERROR,

    CMSG_DELETE_CHAR,
    SMSG_DELETE_CHAR_ERROR,
    CMSG_SELECT_CHAR,

    NUM_MSG_TYPES
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
