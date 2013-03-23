#ifndef DEFINE_H
#define DEFINE_H

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
