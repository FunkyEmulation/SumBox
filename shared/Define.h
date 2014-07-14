#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

enum Breed
{
    UNKNOW,
    FECA,
    OSAMODAS,
    ENUTROF,
    SRAM,
    XELOR,
    ECAFLIP,
    ENIRIPSA,
    IOP,
    CRA,
    SADIDA,
    SACRIEUR,
    PANDAWA
};

enum TimeConstants
{
    IN_MILLISECONDS = 1000
};

enum ClientState
{
    OnDetails,
    OnCheckingVersion,
    OnAuthentication,
    OnQueue,
    Logged
};

#endif
